#ifndef DW4_IGNODE_H
#define DW4_IGNODE_H

struct igMetaObject;
struct igNode;

#ifdef __cplusplus
extern "C" {
#endif

void Gap__Sg__igNode__resetFields(struct igNode *node, int flags);
struct igNode *igNode_Destroy(struct igNode *self, short deleteFlag);

#ifdef __cplusplus
}
#endif

#endif
