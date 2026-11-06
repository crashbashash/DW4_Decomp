extern char igView_Register[];
extern char igView_GetPublishedMetaObject[];
extern char igViewerSceneInfoManagerController_GetVTable[];
extern char thunk_igViewerSceneInfoManagerController_GetMetaObject[];
extern char g_igViewerSceneInfoManagerController_callbackList[];
extern char igViewerSceneInfoManagerController_className[];
extern char g_igViewerSceneInfoManagerController_metaObject[];
int igMetaObject_RegisterClass();
int ViewerLibrary_MarkRegistered();
int igViewerSceneInfoManagerController_InitFields();

void igViewerSceneInfoManagerController_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igViewerSceneInfoManagerController_metaObject,
        igView_Register,
        igView_GetPublishedMetaObject,
        thunk_igViewerSceneInfoManagerController_GetMetaObject,
        igViewerSceneInfoManagerController_className,
        0x14, /* instance size */
        igViewerSceneInfoManagerController_GetVTable,
        &igViewerSceneInfoManagerController_InitFields,
        0, /* extra callback item */
        g_igViewerSceneInfoManagerController_callbackList /* callback list */
    );
}
