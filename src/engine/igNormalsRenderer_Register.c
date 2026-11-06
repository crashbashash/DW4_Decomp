extern char igRenderer_GetPublishedMetaObject[];
extern char igRenderer_Register[];
extern char igNormalsRenderer_GetVTable[];
extern char thunk_igNormalsRenderer_GetMetaObject[];
extern char g_igNormalsRenderer_callbackList[];
extern char igNormalsRenderer_className[];
extern char g_igNormalsRenderer_metaObject[];
int igMetaObject_RegisterClass();
int ViewerLibrary_MarkRegistered();
int igNormalsRenderer_InitFields();

void igNormalsRenderer_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igNormalsRenderer_metaObject,
        igRenderer_Register,
        igRenderer_GetPublishedMetaObject,
        thunk_igNormalsRenderer_GetMetaObject,
        igNormalsRenderer_className,
        0x30, /* instance size */
        igNormalsRenderer_GetVTable,
        &igNormalsRenderer_InitFields,
        0, /* extra callback item */
        g_igNormalsRenderer_callbackList /* callback list */
    );
}
