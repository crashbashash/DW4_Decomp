extern char igObjectPool_Register[];
extern char igRenderPackagePool_GetVTable[];
extern char thunk_igRenderPackagePool_GetMetaObject[];
extern char igObjectPool_GetPublishedMetaObject[];
extern char g_igRenderPackagePool_callbackList[];
extern char igRenderPackagePool_className[];
extern char g_igRenderPackagePool_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igRenderPackagePool_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igRenderPackagePool_metaObject,
        igObjectPool_Register,
        igObjectPool_GetPublishedMetaObject,
        thunk_igRenderPackagePool_GetMetaObject,
        igRenderPackagePool_className,
        0x20, /* instance size */
        igRenderPackagePool_GetVTable,
        0,
        0, /* extra callback item */
        g_igRenderPackagePool_callbackList /* callback list */
    );
}
