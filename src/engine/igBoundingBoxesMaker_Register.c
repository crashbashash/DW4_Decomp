extern char igObject_GetMetaObject_ParentAccessor[];
extern char igBoundingBoxesMaker_GetVTable[];
extern char thunk_igBoundingBoxesMaker_GetMetaObject[];
extern char igObject_Register[];
extern char g_igBoundingBoxesMaker_callbackList[];
extern char igBoundingBoxesMaker_className[];
extern char g_igBoundingBoxesMaker_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igBoundingBoxesMaker_InitFields();

void igBoundingBoxesMaker_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igBoundingBoxesMaker_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igBoundingBoxesMaker_GetMetaObject,
        igBoundingBoxesMaker_className,
        0x28, /* instance size */
        igBoundingBoxesMaker_GetVTable,
        &igBoundingBoxesMaker_InitFields,
        0, /* extra callback item */
        g_igBoundingBoxesMaker_callbackList /* callback list */
    );
}
