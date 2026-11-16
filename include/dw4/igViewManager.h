#ifndef DW4_IGVIEWMANAGER_H
#define DW4_IGVIEWMANAGER_H

struct igMetaObject;
struct igViewManager;
struct igViewMode;
struct igObject;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igViewManager_metaObject;
void igViewManager_SetFrameTime(struct igViewManager *manager, long long frameTime);
void igViewManager_SetSceneUpVector(struct igViewManager *manager, const float *upVector);
/* Fits the view to `scene` under the shared viewer options. */
void igViewManager_ApplyOptions(struct igViewManager *manager, struct igObject *scene);
void igViewManager_PrintViewMatrix(struct igViewManager *manager);
void igViewManager_SetViewMode(struct igViewManager *manager, struct igViewMode *mode);

#ifdef __cplusplus
}
#endif

#endif
