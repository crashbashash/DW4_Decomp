#ifndef DW4_IGVIEWMANAGER_H
#define DW4_IGVIEWMANAGER_H

struct igMetaObject;
struct igViewManager;
struct igViewMode;
struct igObject;
struct igNode;
struct igViewerParameters;

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
void igViewManager_CenterSelection(struct igViewManager *manager, bool resetEye);
void igViewManager_FitSelection(struct igViewManager *manager);
void igViewManager_FrameObject(struct igViewManager *manager, struct igNode *object);
void igViewManager_SynchronizeParameters(struct igViewManager *manager, struct igViewerParameters *parameters);

#ifdef __cplusplus
}
#endif

#endif
