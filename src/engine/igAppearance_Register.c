extern char igNamedObject_GetPublishedMetaObject[];
extern char igAppearance_GetVTable[];
extern char thunk_igAppearance_GetMetaObject[];
extern char igNamedObject_Register[];
extern char g_igAppearance_callbackList[];
extern char igAppearance_className[];
extern char g_igAppearance_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igAppearance_InitFields();

void igAppearance_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igAppearance_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        thunk_igAppearance_GetMetaObject,
        igAppearance_className,
        0x20, /* instance size */
        igAppearance_GetVTable,
        &igAppearance_InitFields,
        0, /* extra callback item */
        g_igAppearance_callbackList /* callback list */
    );
}
