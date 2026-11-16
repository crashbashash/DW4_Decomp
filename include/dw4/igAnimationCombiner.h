#ifndef DW4_IGANIMATIONCOMBINER_H
#define DW4_IGANIMATIONCOMBINER_H

struct igAnimation;
struct igAnimationCombiner;
struct igVec3f;

#ifdef __cplusplus
extern "C" {
#endif

void Vec3f_Set(struct igVec3f *v, float x, float y, float z);
void igAnimationCombiner_AddAnimation(struct igAnimationCombiner *combiner, struct igAnimation *animation, int combineMode, int transitionMode, int status);
int igAnimationCombiner_AddAnimationBlend(struct igAnimationCombiner *combiner, struct igAnimation *animation, int combineMode, int transitionMode, int status, int *priorities, bool perBone, long long transitionTime, float startRatio, float endRatio, long long startTime);
int igAnimationCombiner_RemoveAllStates(struct igAnimationCombiner *combiner);
int igAnimationCombiner_ResetToPose(struct igAnimationCombiner *combiner, struct igAnimationCombiner *source);

#ifdef __cplusplus
}
#endif

#endif
