#ifndef DW4_BEMODELCTRLNODE2_H
#define DW4_BEMODELCTRLNODE2_H

struct beModelCtrlNode2;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct beModelCtrlNode2 *beModelCtrlNode2_Create(int allocator);
long long beModelCtrlNode2_LocalTime(struct beModelCtrlNode2 *node, long long now);
void beModelCtrlNode2_RegisterTraversalFunction(void);
struct igMetaObject *beModelCtrlNode2_ResolveMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif
