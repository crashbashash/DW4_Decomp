extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igTextureMatrixAttr_GetVTable[];
extern char thunk_igTextureMatrixAttr_GetMetaObject[];
extern char igTextureMatrixAttr_className[];
extern char g_igTextureMatrixAttr_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igTextureMatrixAttr_InitFields();

void igTextureMatrixAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igTextureMatrixAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igTextureMatrixAttr_GetMetaObject,
        igTextureMatrixAttr_className,
        0x54, /* instance size */
        igTextureMatrixAttr_GetVTable,
        &igTextureMatrixAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
