#ifndef DW4_IGCOMMONTRAVERSAL_H
#define DW4_IGCOMMONTRAVERSAL_H

struct igCommonTraversal;
struct igGeometry;

#ifdef __cplusplus
extern "C" {
#endif
int igCommonTraversal_TraverseGeometry(struct igCommonTraversal *self, struct igGeometry *geometry);
/* Sets the projection matrix to a perspective between `nearPlane` and `farPlane`: `vfov` (degrees) follows
 * from `hfov` and `aspect`, or with a negative `hfov` the horizontal angle follows from `vfov`. */
void igCommonTraversal_SetPerspective(void *traversal, float hfov, float vfov, float aspect, float nearPlane, float farPlane);
/* Sets the view matrix (_viewMat) and its inverse (_viewMatInv). */
void igCommonTraversal_SetViewMatrix(int traversal, int *matrix);
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
