extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igMatrixOptStateAttr_GetVTable[];
extern char thunk_igMatrixOptStateAttr_GetMetaObject[];
extern char igMatrixOptStateAttr_className[];
extern char g_igMatrixOptStateAttr_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igMatrixOptStateAttr_InitFields();

void igMatrixOptStateAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMatrixOptStateAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igMatrixOptStateAttr_GetMetaObject,
        igMatrixOptStateAttr_className,
        0x10, /* instance size */
        igMatrixOptStateAttr_GetVTable,
        &igMatrixOptStateAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
