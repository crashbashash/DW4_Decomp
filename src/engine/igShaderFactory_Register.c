extern char igNamedObject_GetPublishedMetaObject[];
extern char igShaderFactory_GetVTable[];
extern char thunk_igShaderFactory_GetMetaObject[];
extern char igNamedObject_Register[];
extern char g_igShaderFactory_callbackList[];
extern char igShaderFactory_className[];
extern char g_igShaderFactory_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igShaderFactory_InitFields();

void igShaderFactory_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igShaderFactory_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        thunk_igShaderFactory_GetMetaObject,
        igShaderFactory_className,
        0x18, /* instance size */
        igShaderFactory_GetVTable,
        &igShaderFactory_InitFields,
        0, /* extra callback item */
        g_igShaderFactory_callbackList /* callback list */
    );
}
