extern char igGroup_GetPublishedMetaObject[];
extern char igTransformRecorder_GetVTable[];
extern char thunk_igTransformRecorder_GetMetaObject[];
extern char igGroup_Register[];
extern char igTransformRecorder_className[];
extern char g_igTransformRecorder_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igTransformRecorder_InitFields();

void igTransformRecorder_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igTransformRecorder_metaObject,
        igGroup_Register,
        igGroup_GetPublishedMetaObject,
        thunk_igTransformRecorder_GetMetaObject,
        igTransformRecorder_className,
        0xA0, /* instance size */
        igTransformRecorder_GetVTable,
        &igTransformRecorder_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
