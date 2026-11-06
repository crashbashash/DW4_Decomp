extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igVertexBlendMatrixListAttr_GetVTable[];
extern char thunk_igVertexBlendMatrixListAttr_GetMetaObject[];
extern char g_igVertexBlendMatrixListAttr_callbackList[];
extern char igVertexBlendMatrixListAttr_className[];
extern char g_igVertexBlendMatrixListAttr_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igVertexBlendMatrixListAttr_InitFields();

void igVertexBlendMatrixListAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igVertexBlendMatrixListAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igVertexBlendMatrixListAttr_GetMetaObject,
        igVertexBlendMatrixListAttr_className,
        0x9C, /* instance size */
        igVertexBlendMatrixListAttr_GetVTable,
        &igVertexBlendMatrixListAttr_InitFields,
        0, /* extra callback item */
        g_igVertexBlendMatrixListAttr_callbackList /* callback list */
    );
}
