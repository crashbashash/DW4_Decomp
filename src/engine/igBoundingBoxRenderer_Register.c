extern char igRenderer_GetPublishedMetaObject[];
extern char igRenderer_Register[];
extern char igBoundingBoxRenderer_GetVTable[];
extern char thunk_igBoundingBoxRenderer_GetMetaObject[];
extern char g_igBoundingBoxRenderer_callbackList[];
extern char igBoundingBoxRenderer_className[];
extern char g_igBoundingBoxRenderer_metaObject[];
int igMetaObject_RegisterClass();
int ViewerLibrary_MarkRegistered();
int igBoundingBoxRenderer_InitFields();

void igBoundingBoxRenderer_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igBoundingBoxRenderer_metaObject,
        igRenderer_Register,
        igRenderer_GetPublishedMetaObject,
        thunk_igBoundingBoxRenderer_GetMetaObject,
        igBoundingBoxRenderer_className,
        0x2C, /* instance size */
        igBoundingBoxRenderer_GetVTable,
        &igBoundingBoxRenderer_InitFields,
        0, /* extra callback item */
        g_igBoundingBoxRenderer_callbackList /* callback list */
    );
}
