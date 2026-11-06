extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igStencilStateAttr_GetVTable[];
extern char thunk_igStencilStateAttr_GetMetaObject[];
extern char igStencilStateAttr_className[];
extern char g_igStencilStateAttr_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igStencilStateAttr_InitFields();

void igStencilStateAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igStencilStateAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igStencilStateAttr_GetMetaObject,
        igStencilStateAttr_className,
        0x10, /* instance size */
        igStencilStateAttr_GetVTable,
        &igStencilStateAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
