#ifndef DW4_BEPADMANAGER_H
#define DW4_BEPADMANAGER_H

struct bePadData;
struct bePadManager;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct bePadManager *bePadManager_CreateInstance(int allocator);
void bePadManager_EnsureRegistered(void);
struct igMetaObject *bePadManager_GetOrCreateMetaObject(void);
struct bePadData *bePadManager_GetPadForPlayer(struct bePadManager *self, int player);

extern struct igMetaObject *g_bePadManager_metaObject;

#ifdef __cplusplus
}
#endif

#endif
