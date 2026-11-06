extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igStencilFunctionAttr_GetVTable[];
extern char thunk_igStencilFunctionAttr_GetMetaObject[];
extern char igStencilFunctionAttr_className[];
extern char g_igStencilFunctionAttr_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igStencilFunctionAttr_InitFields();

void igStencilFunctionAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igStencilFunctionAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igStencilFunctionAttr_GetMetaObject,
        igStencilFunctionAttr_className,
        0x28, /* instance size */
        igStencilFunctionAttr_GetVTable,
        &igStencilFunctionAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
