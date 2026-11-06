extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igTexGenMatrixAttr_GetVTable[];
extern char thunk_igTexGenMatrixAttr_GetMetaObject[];
extern char igTexGenMatrixAttr_className[];
extern char g_igTexGenMatrixAttr_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igTexGenMatrixAttr_InitFields();

void igTexGenMatrixAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igTexGenMatrixAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igTexGenMatrixAttr_GetMetaObject,
        igTexGenMatrixAttr_className,
        0x50, /* instance size */
        igTexGenMatrixAttr_GetVTable,
        &igTexGenMatrixAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
