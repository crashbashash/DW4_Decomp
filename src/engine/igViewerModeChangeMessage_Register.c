extern char igMessage_GetPublishedMetaObject[];
extern char igMessage_Register[];
extern char igViewerModeChangeMessage_GetVTable[];
extern char thunk_igViewerModeChangeMessage_GetMetaObject[];
extern char igViewerModeChangeMessage_className[];
extern char g_igViewerModeChangeMessage_metaObject[];
int igMetaObject_RegisterClass();
int ViewerLibrary_MarkRegistered();
int igViewerModeChangeMessage_InitFields();

void igViewerModeChangeMessage_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igViewerModeChangeMessage_metaObject,
        igMessage_Register,
        igMessage_GetPublishedMetaObject,
        thunk_igViewerModeChangeMessage_GetMetaObject,
        igViewerModeChangeMessage_className,
        0x10, /* instance size */
        igViewerModeChangeMessage_GetVTable,
        &igViewerModeChangeMessage_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
