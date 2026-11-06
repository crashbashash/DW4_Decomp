extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igBlendMatricesAttr_GetVTable[];
extern char thunk_igBlendMatricesAttr_GetMetaObject[];
extern char igBlendMatricesAttr_className[];
extern char g_igBlendMatricesAttr_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igBlendMatricesAttr_InitFields();

void igBlendMatricesAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igBlendMatricesAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igBlendMatricesAttr_GetMetaObject,
        igBlendMatricesAttr_className,
        0x18, /* instance size */
        igBlendMatricesAttr_GetVTable,
        &igBlendMatricesAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
