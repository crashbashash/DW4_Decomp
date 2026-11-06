extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igAlphaFunctionAttr_GetVTable[];
extern char thunk_igAlphaFunctionAttr_GetMetaObject[];
extern char igAlphaFunctionAttr_className[];
extern char g_igAlphaFunctionAttr_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igAlphaFunctionAttr_InitFields();

void igAlphaFunctionAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igAlphaFunctionAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igAlphaFunctionAttr_GetMetaObject,
        igAlphaFunctionAttr_className,
        0x14, /* instance size */
        igAlphaFunctionAttr_GetVTable,
        &igAlphaFunctionAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
