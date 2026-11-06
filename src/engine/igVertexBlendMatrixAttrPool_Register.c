extern char igObjectPool_Register[];
extern char igObjectPool_GetPublishedMetaObject[];
extern char igVertexBlendMatrixAttrPool_GetVTable[];
extern char thunk_igVertexBlendMatrixAttrPool_GetMetaObject[];
extern char g_igVertexBlendMatrixAttrPool_callbackList[];
extern char igVertexBlendMatrixAttrPool_className[];
extern char g_igVertexBlendMatrixAttrPool_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igVertexBlendMatrixAttrPool_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igVertexBlendMatrixAttrPool_metaObject,
        igObjectPool_Register,
        igObjectPool_GetPublishedMetaObject,
        thunk_igVertexBlendMatrixAttrPool_GetMetaObject,
        igVertexBlendMatrixAttrPool_className,
        0x20, /* instance size */
        igVertexBlendMatrixAttrPool_GetVTable,
        0,
        0, /* extra callback item */
        g_igVertexBlendMatrixAttrPool_callbackList /* callback list */
    );
}
