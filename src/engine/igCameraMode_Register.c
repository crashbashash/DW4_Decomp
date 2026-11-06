extern char igViewMode_GetPublishedMetaObject[];
extern char igCameraMode_GetVTable[];
extern char thunk_igCameraMode_GetMetaObject[];
extern char igViewMode_Register[];
extern char g_igCameraMode_callbackList[];
extern char igCameraMode_className[];
extern char g_igCameraMode_metaObject[];
int igMetaObject_RegisterClass();
int ViewerLibrary_MarkRegistered();
int igCameraMode_InitFields();

void igCameraMode_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igCameraMode_metaObject,
        igViewMode_Register,
        igViewMode_GetPublishedMetaObject,
        thunk_igCameraMode_GetMetaObject,
        igCameraMode_className,
        0x54, /* instance size */
        igCameraMode_GetVTable,
        &igCameraMode_InitFields,
        0, /* extra callback item */
        g_igCameraMode_callbackList /* callback list */
    );
}
