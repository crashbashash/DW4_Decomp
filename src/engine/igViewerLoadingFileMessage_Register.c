extern char igMessage_GetPublishedMetaObject[];
extern char igMessage_Register[];
extern char igViewerLoadingFileMessage_GetVTable[];
extern char thunk_igViewerLoadingFileMessage_GetMetaObject[];
extern char igViewerLoadingFileMessage_className[];
extern char g_igViewerLoadingFileMessage_metaObject[];
int igMetaObject_RegisterClass();
int ViewerLibrary_MarkRegistered();
int igViewerLoadingFileMessage_InitFields();

void igViewerLoadingFileMessage_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igViewerLoadingFileMessage_metaObject,
        igMessage_Register,
        igMessage_GetPublishedMetaObject,
        thunk_igViewerLoadingFileMessage_GetMetaObject,
        igViewerLoadingFileMessage_className,
        0x10, /* instance size */
        igViewerLoadingFileMessage_GetVTable,
        &igViewerLoadingFileMessage_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
