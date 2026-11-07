#include "dw4/reflected.h"
struct CombinerStateList { char pad[8]; int _count; int _capacity; igAnimationState **_data; };
extern "C" {
long long FUN_001acb10(igAnimationCombiner *);
void FUN_001ac040(igAnimationCombiner *, igAnimationState *);
void FUN_001ad770(igAnimationCombiner *);
int igObject_Destroy(igAnimationState *);
void FUN_001acb50(igAnimationCombiner *c);
}
void FUN_001acb50(igAnimationCombiner *c) {
    long long last = c->_lastCleanStatesTime;
    long long now = FUN_001acb10(c);
    c->_lastCleanStatesTime = now;
    if (now - last >= c->_cleanStatesTimeThreshold) {
        CombinerStateList *list = (CombinerStateList *)c->_animationStateList;
        int i;
        for (i = list->_count - 1; i >= 0; i--) {
            igAnimationState *s = list->_data[i];
            float ticks = (float)(unsigned int)(int)((now - s->_timeRequested) >> 18);
            ticks = ticks * s->_timeScale;
            unsigned long long whole = (unsigned int)ticks;
            long long elapsed = whole << 18;
            long long past = elapsed - s->_blendDuration;
            if (past > c->_cleanStatesTransitionMargin) {
                int mode = s->_transitionMode;
                if (mode == 5) {
                    FUN_001ac040(c, s);
                } else if (mode == 1) {
                    if (s->_baseState != 0) {
                        s->_combineMode = 0;
                        FUN_001ad770(c);
                        ((igAnimationState *)s->_baseState)->_status = 3;
                        {
                            igAnimationState *base = (igAnimationState *)s->_baseState;
                            if (base != 0) {
                                base->_refCount = base->_refCount - 1;
                                if (((unsigned long long)((long long)(int)base->_refCount << 0x29) >> 0x29) == 0) {
                                    igObject_Destroy(base);
                                }
                            }
                        }
                        s->_baseState = 0;
                    } else {
                        FUN_001ac040(c, s);
                    }
                }
            }
        }
    }
}
