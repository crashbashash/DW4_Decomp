#ifndef DW4_IGINTERSECTTRAVERSAL_H
#define DW4_IGINTERSECTTRAVERSAL_H

struct igIntersectTraversal;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igIntersectTraversal_metaObject;
void igIntersectTraversal_Register(void);
void igIntersectTraversal_ResetStacks(struct igIntersectTraversal *traversal);

#ifdef __cplusplus
}
#endif

#endif
