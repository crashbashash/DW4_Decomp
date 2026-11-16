#ifndef DW4_IGACTOR_H
#define DW4_IGACTOR_H

struct igActor;
struct igAnimationCombiner;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igActor_metaObject;
void igActor_SetAnimationSystem(struct igActor *actor, struct igAnimationCombiner *combiner);

#ifdef __cplusplus
}
#endif

#endif
