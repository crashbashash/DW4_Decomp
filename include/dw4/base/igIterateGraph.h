#ifndef DW4_IGITERATEGRAPH_H
#define DW4_IGITERATEGRAPH_H

struct igMetaObject;

struct igObject;
struct igMemoryPoolView;
struct igIterateGraph;
struct igNode;

#ifdef __cplusplus
extern "C" {
#endif
struct igObject *igIterateGraph_Create(struct igMemoryPoolView *pool);

struct igMetaObject *igIterateGraph_GetOrCreateMetaObject(void);

/* Starts a walk of the graph under `root`; returns the first node of class `kind` (or a subclass), null when none. */
struct igNode *FUN_0022ab90(struct igIterateGraph *self, struct igNode *root, struct igMetaObject *kind);
/* The node the walk is at, null when it has finished. */
struct igNode *FUN_0022ac00(struct igIterateGraph *self);
/* Advances to the next node of class `kind` (or a subclass) and returns it, null at the end of the graph. */
struct igNode *FUN_0022ac70(struct igIterateGraph *self, struct igMetaObject *kind);
/* Writes to `matrix` the product of the igTransform matrices on the path to the current node. */
void FUN_0022b0a0(float *matrix, struct igIterateGraph *self);

#ifdef __cplusplus
}
#endif

#endif
