#ifndef DW4_IGCOMMONTRAVERSAL_H
#define DW4_IGCOMMONTRAVERSAL_H

struct igCommonTraversal;
struct igGeometry;
struct igTraversalFunctionList;

#ifdef __cplusplus
extern "C" {
#endif
int igCommonTraversal_TraverseGeometry(struct igCommonTraversal *self, struct igGeometry *geometry);
#ifdef __cplusplus
}
#endif

#endif
