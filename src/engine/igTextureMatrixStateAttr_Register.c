extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igTextureMatrixStateAttr_GetVTable[];
extern char thunk_igTextureMatrixStateAttr_GetMetaObject[];
extern char igTextureMatrixStateAttr_className[];
extern char g_igTextureMatrixStateAttr_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igTextureMatrixStateAttr_InitFields();

void igTextureMatrixStateAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igTextureMatrixStateAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igTextureMatrixStateAttr_GetMetaObject,
        igTextureMatrixStateAttr_className,
        0x14, /* instance size */
        igTextureMatrixStateAttr_GetVTable,
        &igTextureMatrixStateAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
