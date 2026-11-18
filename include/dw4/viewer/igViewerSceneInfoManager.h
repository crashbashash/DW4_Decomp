#ifndef DW4_IGVIEWERSCENEINFOMANAGER_H
#define DW4_IGVIEWERSCENEINFOMANAGER_H

struct igMetaObject;
struct igViewerSceneInfoManager;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igViewerSceneInfoManager_metaObject;
void igViewerSceneInfoManager_EnsureRegistered(void);
struct igMetaObject *igViewerSceneInfoManager_GetOrCreateMetaObject(void);
void igViewerSceneInfoManager_ResetView(struct igViewerSceneInfoManager *manager);
void igViewerSceneInfoManager_CycleGuiVisibility(struct igViewerSceneInfoManager *manager);
void igViewerSceneInfoManager_ResetOperationMode(struct igViewerSceneInfoManager *manager);
void igViewerSceneInfoManager_DebugZoomOut(struct igViewerSceneInfoManager *self);

#ifdef __cplusplus
}

/* A manager member function a viewer action calls (hot keys, menu items). */
typedef void (igViewerSceneInfoManager::*igViewerFunction)();
#endif

#endif
