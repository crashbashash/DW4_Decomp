#ifndef DW4_IGCOMMONTRAVERSAL_H
#define DW4_IGCOMMONTRAVERSAL_H

struct igCommonTraversal;
struct igGeometry;

#ifdef __cplusplus
extern "C" {
#endif
int igCommonTraversal_TraverseGeometry(struct igCommonTraversal *self, struct igGeometry *geometry);
#ifdef __cplusplus
}

#include "dw4/core/igTDataList.h"
#include "dw4/scenegraph/igTraversal.h"

/* igCommonTraversal::travProcs: the traversal function of each node class, which every common traversal starts
 * from. An igTraversalFunctionList is an igTDataList<igTraversalFunctionPtr>; callers of
 * igTraversal_RegisterFunction convert to the reflected igTraversalFunctionList, which types _data as a word. */
extern "C" igTDataList<igTraversalFunctionPtr> *g_igCommonTraversal_travProcs;
#endif

#endif
