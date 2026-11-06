extern char igObjectList_GetPublishedMetaObject[];
extern char igBlendMatrixPaletteAttrList_GetVTable[];
extern char thunk_igBlendMatrixPaletteAttrList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igBlendMatrixPaletteAttrList_callbackList[];
extern char igBlendMatrixPaletteAttrList_className[];
extern char g_igBlendMatrixPaletteAttrList_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igBlendMatrixPaletteAttrList_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igBlendMatrixPaletteAttrList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igBlendMatrixPaletteAttrList_GetMetaObject,
        igBlendMatrixPaletteAttrList_className,
        0x14, /* instance size */
        igBlendMatrixPaletteAttrList_GetVTable,
        0,
        0, /* extra callback item */
        g_igBlendMatrixPaletteAttrList_callbackList /* callback list */
    );
}
