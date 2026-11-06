extern char igObjectPool_Register[];
extern char igObjectPool_GetPublishedMetaObject[];
extern char igBlendMatricesAttrPool_GetVTable[];
extern char thunk_igBlendMatricesAttrPool_GetMetaObject[];
extern char g_igBlendMatricesAttrPool_callbackList[];
extern char igBlendMatricesAttrPool_className[];
extern char g_igBlendMatricesAttrPool_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igBlendMatricesAttrPool_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igBlendMatricesAttrPool_metaObject,
        igObjectPool_Register,
        igObjectPool_GetPublishedMetaObject,
        thunk_igBlendMatricesAttrPool_GetMetaObject,
        igBlendMatricesAttrPool_className,
        0x20, /* instance size */
        igBlendMatricesAttrPool_GetVTable,
        0,
        0, /* extra callback item */
        g_igBlendMatricesAttrPool_callbackList /* callback list */
    );
}
