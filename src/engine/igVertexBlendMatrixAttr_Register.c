extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igVertexBlendMatrixAttr_GetVTable[];
extern char thunk_igVertexBlendMatrixAttr_GetMetaObject[];
extern char igVertexBlendMatrixAttr_className[];
extern char g_igVertexBlendMatrixAttr_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igVertexBlendMatrixAttr_InitFields();

void igVertexBlendMatrixAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igVertexBlendMatrixAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igVertexBlendMatrixAttr_GetMetaObject,
        igVertexBlendMatrixAttr_className,
        0x50, /* instance size */
        igVertexBlendMatrixAttr_GetVTable,
        &igVertexBlendMatrixAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
