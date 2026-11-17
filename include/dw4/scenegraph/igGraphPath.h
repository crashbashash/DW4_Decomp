#ifndef DW4_IGGRAPHPATH_H
#define DW4_IGGRAPHPATH_H

struct igGraphPath;
struct igMatrix44f;
struct igMetaObject;
struct igNode;
struct igNodeList;

#ifdef __cplusplus
extern "C" {
#endif

struct igGraphPath *igGraphPath_Create(int allocator);
struct igMetaObject *igGraphPath_GetOrCreateMetaObject(void);
struct igNode *igGraphPath_GetTail(struct igGraphPath *path);
void igGraphPath_GetTransform(struct igGraphPath *path, struct igMatrix44f *matrix, long long time);
void igGraphPath_SetNodes(struct igGraphPath *path, struct igNodeList *nodes);

#ifdef __cplusplus
}
#endif

#endif
