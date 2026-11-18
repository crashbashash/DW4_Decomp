#ifndef DW4_IGINTERSECTTRAVERSAL_H
#define DW4_IGINTERSECTTRAVERSAL_H

struct CallbackArray;
struct igIntersectTraversal;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igIntersectTraversal_metaObject;
struct igIntersectTraversal *igIntersectTraversal_Destroy(struct igIntersectTraversal *self, short deleteFlag);
struct CallbackArray *igIntersectTraversal_Register(void);
void igIntersectTraversal_ResetStacks(struct igIntersectTraversal *traversal);

struct igMetaObject *igIntersectTraversal_GetOrCreateMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif
