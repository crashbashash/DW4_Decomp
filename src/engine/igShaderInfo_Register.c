extern char igInfo_GetPublishedMetaObject[];
extern char igShaderInfo_GetVTable[];
extern char thunk_igShaderInfo_GetMetaObject[];
extern char igInfo_Register[];
extern char g_igShaderInfo_callbackList[];
extern char igShaderInfo_className[];
extern char g_igShaderInfo_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
extern int thunk_FUN_001d8ab0[4];
int igShaderInfo_InitFields();

void igShaderInfo_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igShaderInfo_metaObject,
        igInfo_Register,
        igInfo_GetPublishedMetaObject,
        thunk_igShaderInfo_GetMetaObject,
        igShaderInfo_className,
        0x18, /* instance size */
        igShaderInfo_GetVTable,
        &igShaderInfo_InitFields,
        thunk_FUN_001d8ab0, /* extra callback item */
        g_igShaderInfo_callbackList /* callback list */
    );
}
