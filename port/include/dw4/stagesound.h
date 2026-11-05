/* dw4/stagesound.h — the sound catalogue of a stage: every beSoundData its sound pack(s) name.
 *
 * A stage file lists its packs as `[<pt>.<entry>]` references. A sound pack holds one
 * beSoundInfo (`_fnameList`, base volume) and the beSoundData records that name each cue, its type, the
 * file (a resident `.sfp` bank or a `[pt.entry]` ADX stream) and the packed sequence selector. The front-end
 * adapter used to prepare a hard-coded name list per scene; this module reads the collection itself, so any
 * stage's cues resolve by name. Opening only reads records. Decoding a cue is explicit and may be done on a
 * worker; the catalogue and the mount must outlive every decode.
 */
#ifndef DW4_STAGESOUND_H
#define DW4_STAGESOUND_H
#include "dw4/audio.h"
#include "dw4/igb.h"
#include "dw4/mount.h"
#include <stdint.h>

#define DW4_STAGESOUND_NAME 48
#define DW4_STAGESOUND_FILE 128

typedef struct {
    char name[DW4_STAGESOUND_NAME];     /* beSoundData._name */
    char file[DW4_STAGESOUND_FILE];     /* beSoundInfo._fnameList[_fnameIdx]: "[pt.entry]" or a bank path; empty if unresolved */
    int type;                           /* beSoundData._type (1/2 streamed tracks, 3/4 resident effects) */
    int fname_idx;                      /* beSoundData._fnameIdx */
    uint32_t memory_idx;                /* beSoundData._memoryIdx: low half sequence group, high half sequence */
    int channel, volume, priority;      /* beSoundData._channel/_volume/_priority */
    int base_volume;                    /* the owning pack's beSoundInfo._baseVolume */
    int pack;                           /* index of the stage reference that holds the record */
} dw4_stagesound_entry;

typedef struct dw4_stagesound dw4_stagesound;
/* dw4_stagesound_decode failures: no file name or bad arguments, an unreadable ADX entry, a bank the pack does not carry, a
 * sequence selector the resolver rejects (unknown, out of range or multi-event), a waveform that does not decode. */
enum { DW4_STAGESOUND_NOFILE = -1, DW4_STAGESOUND_NOSTREAM = -2, DW4_STAGESOUND_NOBANK = -3, DW4_STAGESOUND_NOSEQ = -4, DW4_STAGESOUND_NOWAVE = -5 };

/* `stage` is a manifest file name such as "stag0102.igb". NULL when the stage has no sound pack. */
dw4_stagesound *dw4_stagesound_open(dw4_mount *, const char *stage);
void dw4_stagesound_close(dw4_stagesound *);
/* The opened pack at this index (NULL past the last), for other record classes of the same pack (beSeInfoData). */
dw4_igb *dw4_stagesound_pack_igb(const dw4_stagesound *, unsigned pack);
unsigned dw4_stagesound_count(const dw4_stagesound *);
const dw4_stagesound_entry *dw4_stagesound_at(const dw4_stagesound *, unsigned index);
/* First entry with this name (a duplicate in a later pack never replaces it), or NULL. */
const dw4_stagesound_entry *dw4_stagesound_find(const dw4_stagesound *, const char *name);
/* Decode one cue to a stereo 48 kHz clip: streamed tracks carry their loop points, resident effects resolve
 * sequence -> note -> waveform. Returns 0, or one of the DW4_STAGESOUND_* codes. `label`
 * prefixes a trace line on stdout; NULL decodes silently. */
int dw4_stagesound_decode(const dw4_stagesound *, const dw4_mount *, const dw4_stagesound_entry *, dw4_audio_clip *, const char *label);
/* The raw sequence event bytes of a resident cue (diagnostics: the resolver only follows the single-note subset). */
int dw4_stagesound_events(const dw4_stagesound *, const dw4_stagesound_entry *, const uint8_t **events, size_t *available);
#endif
