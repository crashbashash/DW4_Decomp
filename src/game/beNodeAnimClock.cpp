/* The engine clock counts nanoseconds and every consumer scales it in 2^18 ns ticks. A nonzero
 * _stopTime is returned unchanged. Otherwise the time since the previous update is added to _playTime;
 * when it exceeds 33,333,333 ns the excess is taken off _timeBias, so a long stall does not jump the
 * animation. The node's local time is (ticks * _timeScale) << 18 plus _timeBias; once it reaches the
 * loop end (_loop2Time) the code subtracts the loop end while the time is strictly greater, adds the
 * loop start (_loop1Time) and rebases.
 * Matching constructs: preserve the incoming timestamp and old play count in const locals before
 * reusing the incoming parameter as the elapsed delta. */
#include "dw4/reflected.h"

/* The clock is read in 2^18 ns ticks. */
#define CLOCK_TICK_SHIFT 18

/* Longest per-update step that still advances the animation (about 1/30 s). */
#define NODE_ANIM_MAX_STEP_NS 33333333

/* float -> int64 conversion. */
extern "C" {
long long __fixsfdi(float);
}
/* Rebases _timeBias against the scaled clock. */
extern "C" {
void FUN_0039a960(beNodeAnim *, long long, long long);
long long FUN_0039a9e0(beNodeAnim *self, long long elapsed);
}

long long FUN_0039a9e0(beNodeAnim *self, long long elapsed) {
    float scaledTicks;
    const long long savedNow = elapsed;
    long long loopEnd;
    long long result;

    result = self->_stopTime;
    switch (result) {
    default:
        break;
    case 0: {
        const long long play = self->_playTime;
        elapsed = savedNow - self->_beforeTime;
        self->_playTime = elapsed + play;
        if (NODE_ANIM_MAX_STEP_NS < elapsed) {
            self->_timeBias = self->_timeBias - (elapsed - NODE_ANIM_MAX_STEP_NS);
        }
        self->_beforeTime = savedNow;
        scaledTicks = (float)(unsigned int)(int)(savedNow >> CLOCK_TICK_SHIFT);
        scaledTicks = scaledTicks * self->_timeScale;
        result = __fixsfdi(scaledTicks);
        loopEnd = self->_loop2Time;
        result <<= CLOCK_TICK_SHIFT;
        result += self->_timeBias;
        if (result >= loopEnd) {
            if (loopEnd < result) {
                do {
                    result -= loopEnd;
                } while (loopEnd < result);
            }
            result += self->_loop1Time;
            FUN_0039a960(self, result, savedNow);
        }
    }
    }
    return result;
}
