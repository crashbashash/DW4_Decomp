/* src/sfp.c — the `ps2_DTPK` / `ps2_TBLD` / `ps2_VAGD` sound bank reader.
 *
 * The layout and the decoder are documented in include/dw4/sfp.h.  The decoder is the
 * only nontrivial part; it was recovered by matching ffmpeg's `adpcm_psx` output
 * sample-for-sample on the real banks (tools/verify_sound.py), which pinned three
 * details a plain VAG decoder gets wrong: byte 1 is a control byte (0x07 silences the
 * frame and resets the predictor), the samples are bytes 2..15, and the predictor
 * feeds back the unclamped sample.
 */
#include "dw4/sfp.h"

#include <stdio.h>
#include <string.h>

#define SFP_TBLD_OFF 0x60u
#define SFP_VAGD_HDR 0x20u

static uint32_t le32(const uint8_t *p)
{
    return (uint32_t)p[0] | ((uint32_t)p[1] << 8) |
           ((uint32_t)p[2] << 16) | ((uint32_t)p[3] << 24);
}

static int magic(const uint8_t *p, size_t left, const char *m)
{
    return left >= 8 && memcmp(p, m, 8) == 0;
}

/* The entry-record table's rate field is a u16 stored at record+2.  The table is a run
 * of 16-byte records, and its start is not aligned to the TBLD, so it is found as the
 * longest run of records that carry the same rate. */
static uint32_t find_rate_table(const uint8_t *blob, uint32_t lo, uint32_t hi, uint32_t *rate)
{
    uint32_t best = 0, bestn = 0, p;

    for (p = lo + 2; p + 2 <= hi; p += 2) {
        uint32_t s, n = 0;
        uint16_t r;

        if (blob[p] != 0xc0 || blob[p + 1] != 0x5d)
            continue;
        s = p - 2;
        r = (uint16_t)((uint16_t)blob[s + 2] | ((uint16_t)blob[s + 3] << 8));
        if (r < 8000)
            continue;
        while ((size_t)s + 16 * (n + 1) <= hi &&
               blob[s + 16 * n + 2] == 0xc0 && blob[s + 16 * n + 3] == 0x5d)
            n++;
        if (n > bestn) {
            bestn = n;
            best = s;
        }
    }
    if (bestn)
        *rate = (uint32_t)blob[best + 2] | ((uint32_t)blob[best + 3] << 8);
    return bestn ? best : 0;
}

int dw4_sfp_open(const uint8_t *blob, size_t size, uint32_t off, dw4_sfp_bank *out)
{
    dw4_sfp_bank b;

    if (!blob || !out || (size_t)off + 0x40 > size)
        return -1;
    if (!magic(blob + off, size - off, "ps2_DTPK"))
        return -1;
    memset(&b, 0, sizeof(b));
    b.off = off;
    b.pcm_size = le32(blob + off + 0x0c);
    b.field_10 = le32(blob + off + 0x10);
    b.vag_size = le32(blob + off + 0x18);
    b.header_size = le32(blob + off + 0x1c);
    b.tbl_off = off + SFP_TBLD_OFF;
    if (b.header_size < SFP_TBLD_OFF + 0x20 || b.header_size > 0x10000)
        return -1;
    if ((size_t)b.tbl_off + 0x20 > size || !magic(blob + b.tbl_off, size - b.tbl_off, "ps2_TBLD"))
        return -1;
    b.tbl_len = le32(blob + b.tbl_off + 0x0c);
    b.vag_off = off + b.header_size;
    if ((size_t)b.vag_off + SFP_VAGD_HDR > size ||
        !magic(blob + b.vag_off, size - b.vag_off, "ps2_VAGD"))
        return -1;
    /* The VAGD's own size field must agree with the DTPK's, or the chunks are not
     * the pair this reader thinks they are. */
    if (le32(blob + b.vag_off + 0x0c) != b.vag_size)
        return -1;
    b.vag_data = b.vag_off + SFP_VAGD_HDR;
    if ((size_t)b.vag_data + b.vag_size > size)
        return -1;
    /* Default when a bank carries no entry table; every bank in the shipped packs
     * decodes its records to 24000. */
    b.rate = 24000;
    b.rate_off = find_rate_table(blob, b.tbl_off, b.vag_off, &b.rate);
    *out = b;
    return 0;
}

uint32_t dw4_sfp_scan(const uint8_t *blob, size_t size, dw4_sfp_bank *out, uint32_t cap)
{
    uint32_t n = 0, p;

    if (!blob)
        return 0;
    /* Standalone sbiallse.igb has an unaligned pool (retail DTPK +0xecc7). */
    for (p = 0; (size_t)p + 8 <= size; p++) {
        dw4_sfp_bank b;
        if (memcmp(blob + p, "ps2_DTPK", 8) != 0)
            continue;
        if (dw4_sfp_open(blob, size, p, &b) != 0)
            continue;
        if (n < cap)
            out[n] = b;
        n++;
    }
    return n;
}

uint32_t dw4_sfp_entries(const uint8_t *blob, size_t size, const dw4_sfp_bank *b,
                         dw4_sfp_entry *out, uint32_t cap)
{
    uint32_t n = 0, p, prev;

    (void)size;
    if (!blob || !b || !b->rate_off)
        return 0;
    prev = SFP_VAGD_HDR;                       /* the first entry starts after the VAGD header */
    for (p = b->rate_off; (size_t)p + 16 <= b->vag_off; p += 16) {
        uint32_t end;
        /* A record is {u16 x, u16 rate, u32 a, u32 end, u32 0}; `x` varies per
         * record. The rate is 24000 almost everywhere, but stag0403's bank has 48000 records in the middle of its table,
         * so the table ends where no plausible rate stands (zero padding) or where a value would leave the chunk. */
        unsigned rate = blob[p + 2] | (unsigned)blob[p + 3] << 8;
        if (rate < 8000 || rate > 48000)
            break;
        end = le32(blob + p + 8);
        if (end == 0)
            end = SFP_VAGD_HDR + b->vag_size;  /* the last record closes at the chunk end */
        if (end < prev || end > SFP_VAGD_HDR + b->vag_size)
            break;
        if (out && n < cap) {
            out[n].start = prev;
            out[n].end = end;
            out[n].rate = rate;
        }
        prev = end;
        n++;
    }
    return n;
}

int dw4_sfp_sequence(const uint8_t *blob, size_t size, const dw4_sfp_bank *b, uint32_t memory_idx,
                     const uint8_t **events, size_t *available, uint32_t *tones_off)
{
    uint32_t seq, tones, group = 0, count, index = memory_idx >> 16;
    uint32_t tag = ((memory_idx & 255) << 8) | ((memory_idx >> 8) & 255);
    uint32_t event;
    size_t limit;
    if (!blob || !b || !events || (size_t)b->off + 0xac > size) return -1;
    limit = b->vag_off;
    if (limit > size) return -1;
    seq = le32(blob + b->off + 0xa4);
    tones = le32(blob + b->off + 0xa8);
    if (seq > b->header_size || tones > b->header_size) return -1;
    seq += b->off; tones += b->off;
    if ((size_t)seq + 4 > limit || (size_t)tones + 48 > limit) return -1;
    count = le32(blob + seq);
    if (count > (limit - seq - 4) / 4) return -1;
    for (uint32_t i = 0; i <= count; i++) {
        if ((size_t)seq + 8 + i * 4 > limit) return -1;
        uint32_t row = le32(blob + seq + 4 + i * 4);
        if (row >> 16 == tag) { group = row & 65535; break; }
    }
    if (!group || (size_t)seq + group + 4 > limit) return -1;
    group += seq;
    count = le32(blob + group);
    if (index > count || (size_t)group + 8 + (size_t)index * 4 > limit) return -1;
    event = le32(blob + group + 4 + index * 4);
    if ((size_t)seq + event + 6 > limit) return -1;
    *events = blob + seq + event;
    if (available) *available = limit - (seq + event);
    if (tones_off) *tones_off = tones;
    return 0;
}

int dw4_sfp_resolve_note(const uint8_t *blob, size_t size, const dw4_sfp_bank *b,
                        uint32_t memory_idx, uint32_t *wave, unsigned *velocity)
{
    const uint8_t *ev;
    uint32_t tones, tone;
    size_t limit;
    if (!wave || dw4_sfp_sequence(blob, size, b, memory_idx, &ev, NULL, &tones)) return -1;
    limit = b->vag_off;
    /* A single note event is `c0 df NOTE VELOCITY 80 ff`; the byte after the note is 0x7f in the menu cues and 0x5a..0x78 in
     * 168 gameplay cues. Longer sequences (a second event or a wait) are not followed. */
    if (ev[0] != 0xc0 || ev[1] != 0xdf || ev[3] == 0 || ev[3] > 0x7f || ev[4] != 0x80 || ev[5] != 0xff) return -1;
    /* Tone directory +0x10 owns a 32-byte header followed by 32-byte tones. */
    tone = le32(blob + tones + 8);
    if ((size_t)tones + tone + 32 + (size_t)ev[2] * 32 + 32 > limit) return -1;
    tone += tones + 32 + ev[2] * 32;
    if (blob[tone] != ev[2] || blob[tone + 3] != 1) return -1;
    *wave = blob[tone + 2];
    if (velocity) *velocity = ev[3];
    return 0;
}

int dw4_sfp_resolve(const uint8_t *blob, size_t size, const dw4_sfp_bank *b,
                    uint32_t memory_idx, uint32_t *wave)
{
    return dw4_sfp_resolve_note(blob, size, b, memory_idx, wave, NULL);
}

size_t dw4_vag_decode(const uint8_t *adpcm, size_t len, int16_t *out, size_t cap)
{
    /* Sony VAG predictor pairs: two taps for each of the five filter modes. */
    static const int coef[5][2] = {
        { 0, 0 }, { 60, 0 }, { 115, -52 }, { 98, -55 }, { 122, -60 },
    };
    size_t frames = len / 16, f, n = 0;
    int32_t p1 = 0, p2 = 0;

    for (f = 0; f < frames; f++) {
        const uint8_t *fr = adpcm + f * 16;
        unsigned shift = fr[0] & 0x0f;
        unsigned filt = (fr[0] >> 4) & 0x0f;
        int c1 = 0, c2 = 0;
        unsigned k;

        if (filt < 5) {
            c1 = coef[filt][0];
            c2 = coef[filt][1];
        }
        if (fr[1] == 0x07) {
            /* control byte: an end/silence frame */
            for (k = 0; k < 28 && n < cap; k++)
                out[n++] = 0;
            p1 = p2 = 0;
            continue;
        }
        for (k = 0; k < 28; k++) {
            unsigned byte = fr[2 + (k >> 1)];
            unsigned nib = (k & 1) ? (byte >> 4) : (byte & 0x0f);
            int32_t s = (int32_t)(nib << 12);
            int32_t pred, u;

            if (s & 0x8000)
                s -= 0x10000;                  /* sign-extend the 4-bit sample */
            s = shift ? (s >> shift) : s;
            /* C's `/` truncates toward zero, which is what the reference does; the
             * value fed to the predictor keeps the full range (no int16 clamping). */
            pred = (p1 * c1 + p2 * c2) / 64;
            u = s + pred;
            if (n < cap) {
                if (u > 32767)
                    out[n] = 32767;
                else if (u < -32768)
                    out[n] = -32768;
                else
                    out[n] = (int16_t)u;
                n++;
            }
            p2 = p1;
            p1 = u;
        }
    }
    return n;
}

/* ---- the pack's record layer: bank names and per-sound names ------------------- *
 *
 * The bank container carries sizes but no names; the names live in the pack's own
 * records.  `beCriSfpData` names each bank and its `_pcmSize` equals the DTPK size, so
 * the bank table is exact.  `beSoundData` names each sound and says which bank and
 * entry it is: `_fnameIdx` selects a bank through `beSoundInfo._fnameList`, and
 * `_memoryIdx`'s high 16 bits is a sequence index (#783 corrects #452). The
 * legacy diagnostic name list retains that number; playback uses the full packed
 * selector through dw4_sfp_resolve. Offline the filename list is
 * not decoded, so the groups are matched to banks by their size, which is unique on
 * the shipped packs; a group that matches no bank stays external (e.g. `allse.sfp`).
 */
#include "dw4/igb.h"

#include <stdlib.h>

static const dw4_igb_value *val_of(const dw4_igb_record *r, uint32_t ordinal)
{
    uint32_t i;

    for (i = 0; i < r->nvalues; i++)
        if (r->values[i].ordinal == ordinal)
            return &r->values[i];
    return NULL;
}

/* Walk the pack's longest record chain, handing each record to `cb`. */
static uint32_t walk_records(const dw4_igb *g,
                             void (*cb)(const dw4_igb_record *, void *), void *ctx)
{
    uint32_t off = dw4_igb_find_chain(g, 0x800), n = 0;

    if (!off)
        return 0;
    while (off + 8 <= g->size) {
        uint32_t end;
        dw4_igb_record r;

        if (!dw4_igb_record_end(g, off, &end))
            break;
        if (!dw4_igb_decode(g, off, &r))
            break;
        n++;
        if (cb)
            cb(&r, ctx);
        dw4_igb_record_free(&r);
        off = end;
    }
    return n;
}

struct names_ctx { dw4_sfp_bank *banks; uint32_t nbanks; uint32_t named; };

static void name_cb(const dw4_igb_record *r, void *vctx)
{
    struct names_ctx *c = (struct names_ctx *)vctx;
    const dw4_igb_value *pcm;
    uint32_t i;

    if (!r->class_name || strcmp(r->class_name, "beCriSfpData") != 0 || !r->name)
        return;
    pcm = val_of(r, 5);                     /* beCriSfpData._pcmSize */
    if (!pcm)
        return;
    for (i = 0; i < c->nbanks; i++) {
        if (c->banks[i].name[0] || c->banks[i].pcm_size != pcm->raw)
            continue;
        snprintf(c->banks[i].name, sizeof(c->banks[i].name), "%s", r->name);
        c->named++;
        return;
    }
}

uint32_t dw4_sfp_bank_names(const dw4_igb *g, dw4_sfp_bank *banks, uint32_t nbanks)
{
    struct names_ctx c;

    c.banks = banks;
    c.nbanks = nbanks;
    c.named = 0;
    walk_records(g, name_cb, &c);
    return c.named;
}

struct sounds_ctx { dw4_sfp_sound *s; uint32_t cap, n; };

static void sound_cb(const dw4_igb_record *r, void *vctx)
{
    struct sounds_ctx *c = (struct sounds_ctx *)vctx;
    const dw4_igb_value *fn, *mi;

    if (!r->class_name || strcmp(r->class_name, "beSoundData") != 0 || !r->name)
        return;
    fn = val_of(r, 5);                      /* beSoundData._fnameIdx */
    mi = val_of(r, 6);                      /* beSoundData._memoryIdx */
    if (!fn || !mi || mi->raw == 0xffffffffu)
        return;
    if (c->s && c->n < c->cap) {
        snprintf(c->s[c->n].name, sizeof(c->s[c->n].name), "%s", r->name);
        c->s[c->n].fname_idx = (int)(fn->raw & 0xffffu);
        c->s[c->n].entry = mi->raw >> 16;   /* low byte is the 0xa9 tag */
        c->s[c->n].bank = -1;
    }
    c->n++;
}

uint32_t dw4_sfp_sounds(const dw4_igb *g, dw4_sfp_bank *banks, uint32_t nbanks,
                        dw4_sfp_sound *out, uint32_t cap)
{
    struct sounds_ctx c;
    uint32_t i, j, ngroups = 0;
    int groups[64], taken[64];

    c.s = out;
    c.cap = cap;
    c.n = 0;
    walk_records(g, sound_cb, &c);

    /* Distinct _fnameIdx values, then match each group to the one bank whose entry
     * count equals the group size. */
    for (i = 0; i < c.n && i < cap; i++) {
        int fi = out[i].fname_idx, known = 0;
        for (j = 0; j < ngroups; j++)
            if (groups[j] == fi)
                known = 1;
        if (!known && ngroups < 64)
            groups[ngroups++] = fi;
    }
    for (i = 0; i < nbanks && i < 64; i++)
        taken[i] = 0;
    for (j = 0; j < ngroups; j++) {
        uint32_t size = 0, k, match = nbanks;
        for (k = 0; k < c.n && k < cap; k++)
            if (out[k].fname_idx == groups[j])
                size++;
        for (i = 0; i < nbanks; i++) {
            uint32_t ne = dw4_sfp_entries(g->data, g->size, &banks[i], NULL, 0);
            if (!taken[i] && ne == size) {
                if (match != nbanks) {      /* ambiguous */
                    match = nbanks;
                    break;
                }
                match = i;
            }
        }
        if (match == nbanks)
            continue;
        taken[match] = 1;
        for (k = 0; k < c.n && k < cap; k++) {
            uint32_t ne = dw4_sfp_entries(g->data, g->size, &banks[match], NULL, 0);
            if (out[k].fname_idx == groups[j] && out[k].entry < ne)
                out[k].bank = (int)match;
        }
    }
    return c.n;
}
