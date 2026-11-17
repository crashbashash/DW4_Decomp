#ifndef DW4_BEMETERCTRLNODE_H
#define DW4_BEMETERCTRLNODE_H

struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

void beMeterCtrlNode_RegisterTraversalFunction(void);
struct igMetaObject *beMeterCtrlNode_ResolveMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif
