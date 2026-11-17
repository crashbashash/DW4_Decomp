#ifndef DW4_BEHITLANDMODELTRAVERSAL_H
#define DW4_BEHITLANDMODELTRAVERSAL_H

struct beHitLandModelTraversal;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct beHitLandModelTraversal *beHitLandModelTraversal_Create(int allocator);

extern struct igMetaObject *g_beHitLandModelTraversal_metaObject;

#ifdef __cplusplus
}
#endif

#endif
