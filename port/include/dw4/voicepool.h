/* The retail resident-effect handle allocator (beCri, FUN_0037c130), as a pure function. Retail
 * keeps one pool of effect handles: 4 streamed-ADX handles and 48 sound-bank handles
 * (FUN_0037d310). A play request takes the first idle handle of the right kind; when none is idle
 * it stops and reuses the playing handle with the lowest priority that is not above the request's
 * priority, the oldest first; when none qualifies the play fails. */
#ifndef DW4_VOICEPOOL_H
#define DW4_VOICEPOOL_H
#include <stdint.h>

#define DW4_VOICEPOOL_ADX 4
#define DW4_VOICEPOOL_BANK 48

typedef struct {
    unsigned char adx;      /* the handle carries a streamed-ADX object */
    unsigned char bank;     /* the handle carries a sound-bank (SNDF) object */
    int64_t play_id;        /* 0 when idle, else the request id of the cue it plays */
    int16_t priority;       /* the playing cue's beSoundData._priority */
} dw4_voice_slot;

/* kind 1 picks among ADX handles, kind 0 among sound-bank handles (other kinds consider every handle). `request` is the
 * running request counter before this play. Returns the slot index, or -1 when no handle qualifies; *steal is 1 when the slot
 * is playing and must be stopped before reuse. */
int dw4_voicepool_pick(const dw4_voice_slot *slot, unsigned count, int kind, int16_t priority, int64_t request, int *steal);
#endif
