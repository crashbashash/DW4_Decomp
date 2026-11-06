extern char igViewMode_GetPublishedMetaObject[];
extern char igFlyMode_GetVTable[];
extern char thunk_igFlyMode_GetMetaObject[];
extern char igViewMode_Register[];
extern char g_igFlyMode_callbackList[];
extern char igFlyMode_className[];
extern char g_igFlyMode_metaObject[];
int igMetaObject_RegisterClass();
int ViewerLibrary_MarkRegistered();
int igFlyMode_InitFields();

void igFlyMode_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igFlyMode_metaObject,
        igViewMode_Register,
        igViewMode_GetPublishedMetaObject,
        thunk_igFlyMode_GetMetaObject,
        igFlyMode_className,
        0xA0, /* instance size */
        igFlyMode_GetVTable,
        &igFlyMode_InitFields,
        0, /* extra callback item */
        g_igFlyMode_callbackList /* callback list */
    );
}
