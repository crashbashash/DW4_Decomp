extern char igModel_GetPublishedMetaObject[];
extern char igModel_Register[];
extern char igViewerParameters_GetVTable[];
extern char thunk_igViewerParameters_GetMetaObject[];
extern char g_igViewerParameters_callbackList[];
extern char igViewerParameters_className[];
extern char g_igViewerParameters_metaObject[];
int igMetaObject_RegisterClass();
int ViewerLibrary_MarkRegistered();
int igViewerParameters_InitFields();

void igViewerParameters_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igViewerParameters_metaObject,
        igModel_Register,
        igModel_GetPublishedMetaObject,
        thunk_igViewerParameters_GetMetaObject,
        igViewerParameters_className,
        0x108, /* instance size */
        igViewerParameters_GetVTable,
        &igViewerParameters_InitFields,
        0, /* extra callback item */
        g_igViewerParameters_callbackList /* callback list */
    );
}
