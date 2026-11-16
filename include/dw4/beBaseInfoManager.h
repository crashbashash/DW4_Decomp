#ifndef DW4_BEBASEINFOMANAGER_H
#define DW4_BEBASEINFOMANAGER_H

struct beBaseInfo;
struct beBaseInfoManager;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

int beBaseInfoManager_AddInfo(struct beBaseInfoManager *self, struct beBaseInfo *info);
struct beBaseInfoManager *beBaseInfoManager_Destroy(struct beBaseInfoManager *self, short delete_storage);
void beBaseInfoManager_EnsureRegistered(void);
struct igMetaObject *beBaseInfoManager_GetOrCreateMetaObject(void);
struct igMetaObject *beBaseInfoManager_GetPublishedMetaObject(void);
void *beBaseInfoManager_Register(void);
void beBaseInfoManager_Start(struct beBaseInfoManager *self);
void beBaseInfoManager_Stop(struct beBaseInfoManager *self);

extern struct igMetaObject *g_beBaseInfoManager_metaObject;
extern int g_beBaseInfoManager_vtable[4];

#ifdef __cplusplus
}
#endif

#endif
