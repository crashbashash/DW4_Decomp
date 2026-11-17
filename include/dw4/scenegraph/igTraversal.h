#ifndef DW4_IGTRAVERSAL_H
#define DW4_IGTRAVERSAL_H

struct igMetaObject;
struct igNode;
struct igTraversal;
struct igTraversalFunctionList;

#ifdef __cplusplus
extern "C" {
#endif

void igTraversal_RegisterFunction(struct igTraversalFunctionList *table, struct igMetaObject *meta, void *function);
int igTraversal_TraverseChildren(struct igTraversal *traversal, struct igNode *node);
int igTraversal_TraverseNode(struct igTraversal *traversal, struct igNode *node);

#ifdef __cplusplus
}
#endif

#endif
