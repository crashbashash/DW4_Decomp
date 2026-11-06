extern char igObjectPool_Register[];
extern char igObjectPool_GetPublishedMetaObject[];
extern char igVertexBlendMatrixListAttrPool_GetVTable[];
extern char thunk_igVertexBlendMatrixListAttrPool_GetMetaObject[];
extern char g_igVertexBlendMatrixListAttrPool_callbackList[];
extern char igVertexBlendMatrixListAttrPool_className[];
extern char g_igVertexBlendMatrixListAttrPool_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igVertexBlendMatrixListAttrPool_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igVertexBlendMatrixListAttrPool_metaObject,
        igObjectPool_Register,
        igObjectPool_GetPublishedMetaObject,
        thunk_igVertexBlendMatrixListAttrPool_GetMetaObject,
        igVertexBlendMatrixListAttrPool_className,
        0x20, /* instance size */
        igVertexBlendMatrixListAttrPool_GetVTable,
        0,
        0, /* extra callback item */
        g_igVertexBlendMatrixListAttrPool_callbackList /* callback list */
    );
}
