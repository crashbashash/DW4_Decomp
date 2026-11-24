#ifndef DW4_IGACTOR_H
#define DW4_IGACTOR_H

struct igActor;
struct igAnimationCombiner;
struct igMetaObject;
struct igMetaField;

#ifdef __cplusplus
extern "C" {
#endif

void igActor_SetAnimationSystem(struct igActor *actor, struct igAnimationCombiner *combiner);

#ifdef __cplusplus
}
#endif

#endif
