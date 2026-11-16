#ifndef DW4_IGGRAPHPATH_H
#define DW4_IGGRAPHPATH_H

struct igGraphPath;
struct igMatrix44f;
struct igMetaObject;
struct igNode;

#ifdef __cplusplus
extern "C" {
#endif

struct igGraphPath *igGraphPath_Create(int allocator);
struct igMetaObject *igGraphPath_GetOrCreateMetaObject(void);
struct igNode *igGraphPath_GetTail(struct igGraphPath *path);
void igGraphPath_GetTransform(struct igGraphPath *path, struct igMatrix44f *matrix, int time);

#ifdef __cplusplus
}
#endif

#endif
