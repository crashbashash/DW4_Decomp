extern char igShaderFactory_Register[];
extern char igIniShaderFactory_GetVTable[];
extern char thunk_igIniShaderFactory_GetMetaObject[];
extern char igShaderFactory_GetPublishedMetaObject[];
extern char g_igIniShaderFactory_callbackList[];
extern char igIniShaderFactory_className[];
extern char g_igIniShaderFactory_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igIniShaderFactory_InitFields();

void igIniShaderFactory_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igIniShaderFactory_metaObject,
        igShaderFactory_Register,
        igShaderFactory_GetPublishedMetaObject,
        thunk_igIniShaderFactory_GetMetaObject,
        igIniShaderFactory_className,
        0x3C, /* instance size */
        igIniShaderFactory_GetVTable,
        &igIniShaderFactory_InitFields,
        0, /* extra callback item */
        g_igIniShaderFactory_callbackList /* callback list */
    );
}
