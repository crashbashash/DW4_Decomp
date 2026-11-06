extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igVertexBlendStateAttr_GetVTable[];
extern char thunk_igVertexBlendStateAttr_GetMetaObject[];
extern char igVertexBlendStateAttr_className[];
extern char g_igVertexBlendStateAttr_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igVertexBlendStateAttr_InitFields();

void igVertexBlendStateAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igVertexBlendStateAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igVertexBlendStateAttr_GetMetaObject,
        igVertexBlendStateAttr_className,
        0x10, /* instance size */
        igVertexBlendStateAttr_GetVTable,
        &igVertexBlendStateAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
