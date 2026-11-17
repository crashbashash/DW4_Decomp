#ifndef DW4_BENODEANIM_H
#define DW4_BENODEANIM_H

struct beNodeAnim;
struct igCommonTraversal;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

void beNodeAnim_RegisterTraversalFunction(void);
struct igMetaObject *beNodeAnim_ResolveMetaObject(void);
void beNodeAnim_SetTime(struct beNodeAnim *node, long long time, long long now);
int beNodeAnim_Traverse(struct beNodeAnim *node, struct igCommonTraversal *traversal);
long long beNodeAnim_UpdateTime(struct beNodeAnim *node, long long now);

#ifdef __cplusplus
}
#endif

#endif
