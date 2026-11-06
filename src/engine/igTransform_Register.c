extern char igGroup_GetPublishedMetaObject[];
extern char igTransform_GetVTable[];
extern char thunk_igTransform_GetMetaObject[];
extern char igGroup_Register[];
extern char g_igTransform_callbackList[];
extern char igTransform_className[];
extern char g_igTransform_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igTransform_InitFields();

void igTransform_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igTransform_metaObject,
        igGroup_Register,
        igGroup_GetPublishedMetaObject,
        thunk_igTransform_GetMetaObject,
        igTransform_className,
        0x6C, /* instance size */
        igTransform_GetVTable,
        &igTransform_InitFields,
        0, /* extra callback item */
        g_igTransform_callbackList /* callback list */
    );
}
