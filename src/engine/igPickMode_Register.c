extern char igViewMode_GetPublishedMetaObject[];
extern char igPickMode_GetVTable[];
extern char thunk_igPickMode_GetMetaObject[];
extern char igViewMode_Register[];
extern char g_igPickMode_callbackList[];
extern char igPickMode_className[];
extern char g_igPickMode_metaObject[];
int igMetaObject_RegisterClass();
int ViewerLibrary_MarkRegistered();
int igPickMode_InitFields();

void igPickMode_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igPickMode_metaObject,
        igViewMode_Register,
        igViewMode_GetPublishedMetaObject,
        thunk_igPickMode_GetMetaObject,
        igPickMode_className,
        0xBC, /* instance size */
        igPickMode_GetVTable,
        &igPickMode_InitFields,
        0, /* extra callback item */
        g_igPickMode_callbackList /* callback list */
    );
}
