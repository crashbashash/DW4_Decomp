#ifndef DW4_IGACTOR_H
#define DW4_IGACTOR_H

struct igActor;
struct igAnimationCombiner;
struct igMetaObject;
struct igMetaField;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igActor_metaObject;
extern struct igMetaField *g_igActor_boneMatrixCacheArrayMetaField;
extern struct igMetaField *g_igActor_blendMatrixCacheArrayMetaField;
void igActor_SetAnimationSystem(struct igActor *actor, struct igAnimationCombiner *combiner);

#ifdef __cplusplus
}
#endif

#endif
