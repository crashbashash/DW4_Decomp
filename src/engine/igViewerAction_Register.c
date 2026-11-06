extern char igAction_GetPublishedMetaObject[];
extern char igAction_Register[];
extern char igViewerAction_GetVTable[];
extern char thunk_igViewerAction_GetMetaObject[];
extern char g_igViewerAction_callbackList[];
extern char igViewerAction_className[];
extern char g_igViewerAction_metaObject[];
int igMetaObject_RegisterClass();
int ViewerLibrary_MarkRegistered();
int igViewerAction_InitFields();

void igViewerAction_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igViewerAction_metaObject,
        igAction_Register,
        igAction_GetPublishedMetaObject,
        thunk_igViewerAction_GetMetaObject,
        igViewerAction_className,
        0x18, /* instance size */
        igViewerAction_GetVTable,
        &igViewerAction_InitFields,
        0, /* extra callback item */
        g_igViewerAction_callbackList /* callback list */
    );
}
