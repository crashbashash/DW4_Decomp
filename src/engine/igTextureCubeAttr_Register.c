extern char igTextureCubeAttr_GetVTable[];
extern char thunk_igTextureCubeAttr_GetMetaObject[];
extern char igTextureAttr_GetPublishedMetaObject[];
extern char igTextureAttr_Register[];
extern char g_igTextureCubeAttr_callbackList[];
extern char igTextureCubeAttr_className[];
extern char g_igTextureCubeAttr_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igTextureCubeAttr_InitFields();

void igTextureCubeAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igTextureCubeAttr_metaObject,
        igTextureAttr_Register,
        igTextureAttr_GetPublishedMetaObject,
        thunk_igTextureCubeAttr_GetMetaObject,
        igTextureCubeAttr_className,
        0x68, /* instance size */
        igTextureCubeAttr_GetVTable,
        &igTextureCubeAttr_InitFields,
        0, /* extra callback item */
        g_igTextureCubeAttr_callbackList /* callback list */
    );
}
