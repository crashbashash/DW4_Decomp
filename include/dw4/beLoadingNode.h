#ifndef DW4_BELOADINGNODE_H
#define DW4_BELOADINGNODE_H

struct beLoadingNode;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

int beLoadingNode_IsPastPlayLimit(struct beLoadingNode *node);
void beLoadingNode_Lock(struct beLoadingNode *node);
void beLoadingNode_RegisterTraversalFunction(void);
struct igMetaObject *beLoadingNode_ResolveMetaObject(void);

extern struct igMetaObject *g_beLoadingNode_metaObject;

#ifdef __cplusplus
}
#endif

#endif
