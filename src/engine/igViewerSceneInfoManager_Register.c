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
        0, /* abstract */
        g_igViewerSceneInfoManager_metaObject,
        igInfoManager_Register,
        igInfoManager_GetPublishedMetaObject,
        thunk_igViewerSceneInfoManager_GetMetaObject,
        igViewerSceneInfoManager_className,
        0xC8, /* instance size */
        igViewerSceneInfoManager_GetVTable,
        &igViewerSceneInfoManager_InitFields_00459ee0[0],                               /* field adder: InitFields, registers the reflected fields */
        0, /* extra callback item */
        g_igViewerSceneInfoManager_callbackList /* callback list */
    );
}
