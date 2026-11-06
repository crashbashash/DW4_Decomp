/* What the retail stream player does with one music or ambience request (beCri, FUN_0037c2c0), as
 * a pure function. A request carries a beSoundData type (1 music, 2 ambience; the player only
 * handles those) and memory index (-1 for an ADX file). When the slot's voice is still playing the
 * request does not start: it arms a fade-down of the playing track (only if no ramp runs) and
 * returns 0, and the caller retries later. Otherwise it sets the voice level to volume + base,
 * starts the file and, on success, returns the next request id. */
#ifndef DW4_STREAMPLAYER_H
#define DW4_STREAMPLAYER_H
#include <stdint.h>

/* Leaf operations in the order retail performs them. */
enum { DW4_STREAM_NONE = 0, DW4_STREAM_CHECK = 1, DW4_STREAM_FADE = 2, DW4_STREAM_PAUSE = 3, DW4_STREAM_LEVEL = 4, DW4_STREAM_START = 5,
       DW4_STREAM_UNPAUSE = 6, DW4_STREAM_NAME = 7 };

typedef struct {
    int64_t seq;          /* the new request id, or 0 when nothing started */
    int ops[8];           /* DW4_STREAM_* in call order, terminated by DW4_STREAM_NONE */
    int level;            /* the level set before starting (volume + base) when DW4_STREAM_LEVEL ran */
    int clear_skip;       /* the one-shot "start paused" flag was consumed */
} dw4_stream_decision;

/* slot_state: the voice query result (1 playing, 0 finished, -1 error). fade_running: the slot's ramp mode is not 0. start_ok: the file
 * started. skip_pause: beCri._pauseOnetime. */
void dw4_stream_decide(int type, int memory_idx, int slot_state, int fade_running, int start_ok, int skip_pause, int volume, int base,
                       int64_t request, dw4_stream_decision *out);
#endif
