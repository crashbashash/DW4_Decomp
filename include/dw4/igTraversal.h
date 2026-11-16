#ifndef DW4_IGTRAVERSAL_H
#define DW4_IGTRAVERSAL_H

struct igNode;
struct igTraversal;

#ifdef __cplusplus
extern "C" {
#endif

int igTraversal_TraverseChildren(struct igTraversal *traversal, struct igNode *node);
int igTraversal_TraverseNode(struct igTraversal *traversal, struct igNode *node);

#ifdef __cplusplus
}
#endif

#endif
