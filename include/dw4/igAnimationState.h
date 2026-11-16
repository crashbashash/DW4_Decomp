#ifndef DW4_IGANIMATIONSTATE_H
#define DW4_IGANIMATIONSTATE_H

struct igAnimationState;

#ifdef __cplusplus
extern "C" {
#endif

void igAnimationState_UpdateLocalTime(struct igAnimationState *state, long long time);

#ifdef __cplusplus
}
#endif

#endif
