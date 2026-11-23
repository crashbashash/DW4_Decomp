#ifndef DW4_IGTRAVERSAL_H
#define DW4_IGTRAVERSAL_H

struct igMetaObject;
struct igNode;
struct igTraversal;
struct igObject;
struct igTraversalFunctionList;

/* What a traversal calls for an object of one class: an igTraversalFunctionList holds one per class. */
typedef int igTraversalFunction(struct igTraversal *traversal, struct igObject *object);
typedef igTraversalFunction *igTraversalFunctionPtr;

/* What a traversal calls to select a node: 0 traverses it, 1 ignores it, 2 passes through to its children (the
 * kit's IG_SELECT_NODE_TRAVERSE, IG_SELECT_NODE_IGNORE, IG_SELECT_NODE_PASS_THROUGH). */
typedef int igTravNodeSelectFunction(struct igTraversal *traversal, struct igNode *node);

#ifdef __cplusplus
extern "C" {
#endif

int igTraversal_TraverseChildren(struct igTraversal *traversal, struct igNode *node);

#ifdef __cplusplus
}
#endif

#endif
