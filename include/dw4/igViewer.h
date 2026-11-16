#ifndef DW4_IGVIEWER_H
#define DW4_IGVIEWER_H

struct igMetaObject;
struct igMetaField;
struct igViewerLoadingFileMessage;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igViewerSceneInfoManager_metaObject;
extern struct igMetaField *g_igViewerParameters_showGuiMetaField;
extern struct igMetaField *g_igViewerParameters_showBoundingBoxMetaField;
extern struct igMetaField *g_igViewerParameters_showNormalsMetaField;
extern struct igMetaField *g_igViewerParameters_flushFramesMetaField;

struct igViewerLoadingFileMessage *igViewerLoadingFileMessage_Create(int allocator);

#ifdef __cplusplus
}
#endif

#endif
