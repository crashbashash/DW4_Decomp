/* 0x00459e50 igViewerSceneInfoManager_Register: registers class igViewerSceneInfoManager with the object system, derived from igInfoManager.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igInfoManager_GetPublishedMetaObject[];
extern char igInfoManager_Register[];
extern char igViewerSceneInfoManager_GetVTable[];
extern char thunk_igViewerSceneInfoManager_GetMetaObject[];
extern char g_igViewerSceneInfoManager_callbackList[];
extern char igViewerSceneInfoManager_className[];
extern char g_igViewerSceneInfoManager_metaObject[];
int igMetaObject_RegisterClass();
int ViewerLibrary_MarkRegistered();
extern int igViewerSceneInfoManager_InitFields_00459ee0[4];
void igViewerSceneInfoManager_Register(void) {
    ViewerLibrary_MarkRegistered();  /* one-shot static-init latch (sets a gp-relative byte flag once) */
    igMetaObject_RegisterClass(
        0,                                              /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igViewerSceneInfoManager_metaObject, /* published MetaObject slot */
        igInfoManager_Register,                         /* base class registrar */
        igInfoManager_GetPublishedMetaObject,  /* base class MetaObject accessor */
        thunk_igViewerSceneInfoManager_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igViewerSceneInfoManager_className,  /* class name */
        0xC8,                                           /* instance size */
        igViewerSceneInfoManager_GetVTable,             /* vtable getter */
        &igViewerSceneInfoManager_InitFields_00459ee0[0],                               /* field adder: InitFields, registers the reflected fields */
        0,                                              /* extra callback item */
        g_igViewerSceneInfoManager_callbackList  /* callback list */
    );
}
