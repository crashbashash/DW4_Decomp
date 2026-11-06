extern char igNamedObject_GetPublishedMetaObject[];
extern char igSkin_GetVTable[];
extern char thunk_igSkin_GetMetaObject[];
extern char igNamedObject_Register[];
extern char g_igSkin_callbackList[];
extern char igSkin_className[];
extern char g_igSkin_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igSkin_InitFields();

void igSkin_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igSkin_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        thunk_igSkin_GetMetaObject,
        igSkin_className,
        0x14, /* instance size */
        igSkin_GetVTable,
        &igSkin_InitFields,
        0, /* extra callback item */
        g_igSkin_callbackList /* callback list */
    );
}
