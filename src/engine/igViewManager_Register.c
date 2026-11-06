extern char igEventReceiver_GetPublishedMetaObject[];
extern char igEventReceiver_Register[];
extern char igViewManager_GetVTable[];
extern char thunk_igViewManager_GetMetaObject[];
extern char g_igViewManager_callbackList[];
extern char igViewManager_className[];
extern char g_igViewManager_metaObject[];
int igMetaObject_RegisterClass();
int ViewerLibrary_MarkRegistered();
int igViewManager_InitFields();

void igViewManager_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igViewManager_metaObject,
        igEventReceiver_Register,
        igEventReceiver_GetPublishedMetaObject,
        thunk_igViewManager_GetMetaObject,
        igViewManager_className,
        0x54, /* instance size */
        igViewManager_GetVTable,
        &igViewManager_InitFields,
        0, /* extra callback item */
        g_igViewManager_callbackList /* callback list */
    );
}
