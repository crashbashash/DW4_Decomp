#ifndef DW4_IGNODE_H
#define DW4_IGNODE_H

struct igMetaObject;
struct igNode;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igGeometry_metaObject;
void Gap__Sg__igNode__resetFields(struct igNode *node);
void igNode_EnsureRegistered(void);
struct igMetaObject *igNode_GetOrCreateMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif
