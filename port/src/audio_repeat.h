/* beSound SE repeat admission, from 0x0039eef0..0x0039effc.
 * Deadlines use the supplied game clock, independent of SDL/device time. */
#ifndef DW4_AUDIO_REPEAT_H
#define DW4_AUDIO_REPEAT_H
#include <stdint.h>
typedef struct { uint64_t until; int valid; } dw4_audio_repeat;
static inline int dw4_audio_repeat_allowed(const dw4_audio_repeat *r, uint64_t now)
{
    return !r->valid || (int64_t)now >= (int64_t)r->until;
}
static inline void dw4_audio_repeat_started(dw4_audio_repeat *r, uint64_t now)
{
    r->until = now + UINT64_C(0x2faf07e);
    r->valid = 1;
}
#endif
