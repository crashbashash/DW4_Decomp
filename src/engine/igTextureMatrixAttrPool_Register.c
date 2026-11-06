extern char igObjectPool_Register[];
extern char igObjectPool_GetPublishedMetaObject[];
extern char igTextureMatrixAttrPool_GetVTable[];
extern char thunk_igTextureMatrixAttrPool_GetMetaObject[];
extern char g_igTextureMatrixAttrPool_callbackList[];
extern char igTextureMatrixAttrPool_className[];
extern char g_igTextureMatrixAttrPool_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igTextureMatrixAttrPool_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igTextureMatrixAttrPool_metaObject,
        igObjectPool_Register,
        igObjectPool_GetPublishedMetaObject,
        thunk_igTextureMatrixAttrPool_GetMetaObject,
        igTextureMatrixAttrPool_className,
        0x20, /* instance size */
        igTextureMatrixAttrPool_GetVTable,
        0,
        0, /* extra callback item */
        g_igTextureMatrixAttrPool_callbackList /* callback list */
    );
}
