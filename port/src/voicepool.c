#include "dw4/voicepool.h"

/* Mirrors FUN_0037c130: a handle is capable unless (kind 1 and no ADX object) or (kind 0 and no sound-bank object). */
static int capable(const dw4_voice_slot *s, int kind)
{
    return !(kind == 1 && !s->adx) && !(kind == 0 && !s->bank);
}

int dw4_voicepool_pick(const dw4_voice_slot *slot, unsigned count, int kind, int16_t priority, int64_t request, int *steal)
{
    int64_t best_key = request;
    int best_rank = 0x7fff, best = -1;
    unsigned i;
    if (steal) *steal = 0;
    for (i = 0; i < count; i++)
        if (capable(&slot[i], kind) && slot[i].play_id == 0) return (int)i;
    for (i = 0; i < count; i++) {
        if (!capable(&slot[i], kind)) continue;
        if (slot[i].priority <= priority && slot[i].play_id < best_key && slot[i].priority <= (int16_t)best_rank) {
            best_key = slot[i].play_id;
            best_rank = slot[i].priority;
            best = (int)i;
        }
    }
    if (best != -1 && steal) *steal = 1;
    return best;
}
