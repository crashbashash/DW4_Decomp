#ifndef DW4_BEFILELISTINFOMANAGER_H
#define DW4_BEFILELISTINFOMANAGER_H

struct beFileListInfoManager;
struct igMetaObject;
struct igStringRefList;

#ifdef __cplusplus
extern "C" {
#endif

int beFileListInfoManager_AddReadInfos(struct beFileListInfoManager *self);
struct beFileListInfoManager *beFileListInfoManager_CreateInstance(int allocator);
int beFileListInfoManager_LoadNextFile(struct beFileListInfoManager *self, struct igStringRefList *fileNames);

extern struct igMetaObject *g_beFileListInfoManager_metaObject;

#ifdef __cplusplus
}
#endif

#endif
