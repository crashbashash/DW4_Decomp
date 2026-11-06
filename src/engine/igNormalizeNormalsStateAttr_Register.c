extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igNormalizeNormalsStateAttr_GetVTable[];
extern char thunk_igNormalizeNormalsStateAttr_GetMetaObject[];
extern char igNormalizeNormalsStateAttr_className[];
extern char g_igNormalizeNormalsStateAttr_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igNormalizeNormalsStateAttr_InitFields();

void igNormalizeNormalsStateAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igNormalizeNormalsStateAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igNormalizeNormalsStateAttr_GetMetaObject,
        igNormalizeNormalsStateAttr_className,
        0x10, /* instance size */
        igNormalizeNormalsStateAttr_GetVTable,
        &igNormalizeNormalsStateAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
