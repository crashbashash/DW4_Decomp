/* dw4/sfp.h — CRI "ps2_" sound banks (the `.sfp` container inside a stage's sound pack).
 *
 * A stage is delivered as a pair of NDMW.AFS entries: the bigger is the model/setup pack,
 * the smaller is its **sound + SE pack** (finding #431).  That pack is an igBinary container
 * whose *content pool* holds six `ps2_DTPK` banks (finding #450) — one per entity, named by
 * the pack's `beCriSfpData` records (`e_goburi.sfp`, `common_blst.sfp`, …).
 *
 * A bank is three chunks at fixed offsets:
 *
 *   +0x000  ps2_DTPK   16-byte header: {magic, 0x4102, pcm_size, field_10,
 *                                       0, vag_size, header_size}
 *   +0x060  ps2_TBLD   {magic, 0x4102, length}, decode tables, then a trailing
 *                      table of 16-byte per-entry records {u16 0, u16 rate, u32 a,
 *                      u32 end, u32 0} — the `end` fields are the entry boundaries
 *   +0x800  ps2_VAGD   {magic, 0x4102, vag_size}, 0x20-byte header, then ADPCM
 *
 * All fields above are little-endian, including the record sample rate.
 *
 * The ADPCM is Sony **VAG** with a 16-byte frame, but with a twist ffmpeg's decoder
 * confirms: byte 0 is shift (low nibble) / filter (high nibble), byte 1 is a *control*
 * byte (0x07 = silence / end of entry), and the 28 samples are the nibbles of bytes
 * 2..15 (low nibble first).  The predictor keeps the **unclamped** sample; only the
 * output is clamped to int16.  `dw4_vag_decode` reproduces ffmpeg's `adpcm_psx` output
 * sample-for-sample over all six banks (tools/verify_sound.py).
 */
#ifndef DW4_SFP_H
#define DW4_SFP_H

#include <stddef.h>
#include <stdint.h>

struct dw4_igb;

/* One `ps2_DTPK` bank, with the offsets its chunks resolve to. */
typedef struct {
    uint32_t off;          /* DTPK chunk offset in the pack */
    uint32_t pcm_size;     /* DTPK +0x0c (matches beCriSfpData `_pcmSize`) */
    uint32_t field_10;     /* DTPK +0x10 (800..1216; role unproven) */
    uint32_t vag_size;     /* DTPK +0x18: ADPCM bytes in the VAGD chunk */
    uint32_t header_size;  /* DTPK +0x1c: VAGD's offset (always 0x800 so far) */
    uint32_t tbl_off;      /* TBLD chunk offset (off + 0x60) */
    uint32_t tbl_len;      /* TBLD length field (excludes the trailing record table) */
    uint32_t vag_off;      /* VAGD chunk offset (off + header_size) */
    uint32_t vag_data;     /* first ADPCM byte (vag_off + 0x20) */
    uint32_t rate;         /* sample rate, from the TBLD's entry records */
    uint32_t rate_off;     /* offset of the entry-record table in the pack */
    char name[40];         /* `<bank>.sfp`, from the pack's beCriSfpData records */
} dw4_sfp_bank;

/* One sound inside a bank: a byte range of the VAGD chunk's ADPCM. */
typedef struct {
    uint32_t start;        /* offset within the VAGD chunk (>= 0x20) */
    uint32_t end;          /* one past the entry's last ADPCM byte */
    uint32_t rate;         /* this entry's sample rate: 24000 in most records, 48000 in some stag0403 sounds */
} dw4_sfp_entry;

/* A named sound, from the pack's `beSoundData` records (finding #452):
 * `_fnameIdx` picks the bank through `beSoundInfo._fnameList` and `_memoryIdx`'s high
 * 16 bits is a sequence index, not a waveform index. `dw4_sfp_resolve` follows
 * its group tag and note-to-waveform routing. `bank` is -1 for a sound whose bank is not in
 * this pack (e.g. the global `allse.sfp`). */
typedef struct {
    char name[48];         /* beSoundData._name */
    int bank;              /* index into the dw4_sfp_scan array, or -1 */
    uint32_t entry;        /* legacy diagnostic: sequence index, not waveform */
    int fname_idx;         /* beSoundData._fnameIdx, for diagnostics */
} dw4_sfp_sound;

/* Read a pack's `beCriSfpData` records and fill `banks[i].name` (`<bank>.sfp`) by
 * matching each record's `_pcmSize` against the bank's DTPK size.  Returns how many
 * banks were named.  `g` must be the pack opened as igBinary. */
uint32_t dw4_sfp_bank_names(const struct dw4_igb *g, dw4_sfp_bank *banks, uint32_t nbanks);

/* Read a pack's `beSoundData` records and resolve each to a (bank, entry): the
 * records group by `_fnameIdx`, and each group's size equals its bank's entry count,
 * which is how the group is matched to a bank (unique per pack; `allse.sfp` and other
 * out-of-pack banks stay -1).  Returns the number of sounds (may exceed `cap`). */
uint32_t dw4_sfp_sounds(const struct dw4_igb *g, dw4_sfp_bank *banks, uint32_t nbanks,
                        dw4_sfp_sound *out, uint32_t cap);

/* Parse the bank whose DTPK chunk sits at `off`.  Returns 0, or -1 if the chunk is
 * not a valid `ps2_DTPK` / `ps2_TBLD` / `ps2_VAGD` triple (offsets are self-checked by
 * the VAGD size field and the chunk bounds). */
int dw4_sfp_open(const uint8_t *blob, size_t size, uint32_t off, dw4_sfp_bank *out);

/* Enumerate every `ps2_DTPK` in a pack.  Returns the count (which may exceed `cap`). */
uint32_t dw4_sfp_scan(const uint8_t *blob, size_t size, dw4_sfp_bank *out, uint32_t cap);

/* Read a bank's entry table into `out`.  Returns the entry count (may exceed `cap`).
 * An empty/absent table means one entry spanning the whole chunk. */
uint32_t dw4_sfp_entries(const uint8_t *blob, size_t size, const dw4_sfp_bank *b,
                         dw4_sfp_entry *out, uint32_t cap);

/* Resolve a resident `_memoryIdx` through the bank's sequence and tone tables.
 * Supports the single-note sequences used by front-end/arrival cues. Rejects
 * multi-event sequences rather than silently playing an unrelated waveform. */
/* The raw event bytes of a packed sequence selector (group row, then sequence offset), and the tone directory offset. Used by
 * dw4_sfp_resolve for the single-note subset and by diagnostics for the rest. `available` is the byte count to the end of the
 * header region. Returns 0, or -1 for an unknown group/sequence. */
int dw4_sfp_sequence(const uint8_t *blob, size_t size, const dw4_sfp_bank *b, uint32_t memory_idx,
                     const uint8_t **events, size_t *available, uint32_t *tones_off);
/* The same, also reporting the event's velocity byte (1..0x7f). The mixer does not apply it yet. */
int dw4_sfp_resolve_note(const uint8_t *blob, size_t size, const dw4_sfp_bank *b, uint32_t memory_idx, uint32_t *wave, unsigned *velocity);
int dw4_sfp_resolve(const uint8_t *blob, size_t size, const dw4_sfp_bank *b,
                    uint32_t memory_idx, uint32_t *wave);

/* Decode a VAG stream (16-byte frames) to signed 16-bit mono samples.  Writes at most
 * `cap` samples and returns how many.  A `ps2_VAGD` header is *not* expected here: pass
 * the ADPCM bytes (bank->vag_data) and their length (bank->vag_size). */
size_t dw4_vag_decode(const uint8_t *adpcm, size_t len, int16_t *out, size_t cap);

#endif /* DW4_SFP_H */
