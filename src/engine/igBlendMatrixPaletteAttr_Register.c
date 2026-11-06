extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igBlendMatrixPaletteAttr_GetVTable[];
extern char thunk_igBlendMatrixPaletteAttr_GetMetaObject[];
extern char igBlendMatrixPaletteAttr_className[];
extern char g_igBlendMatrixPaletteAttr_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igBlendMatrixPaletteAttr_InitFields();

void igBlendMatrixPaletteAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igBlendMatrixPaletteAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igBlendMatrixPaletteAttr_GetMetaObject,
        igBlendMatrixPaletteAttr_className,
        0x1C, /* instance size */
        igBlendMatrixPaletteAttr_GetVTable,
        &igBlendMatrixPaletteAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
