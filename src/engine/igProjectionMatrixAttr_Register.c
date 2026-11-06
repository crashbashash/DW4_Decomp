extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igProjectionMatrixAttr_GetVTable[];
extern char thunk_igProjectionMatrixAttr_GetMetaObject[];
extern char igProjectionMatrixAttr_className[];
extern char g_igProjectionMatrixAttr_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igProjectionMatrixAttr_InitFields();

void igProjectionMatrixAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igProjectionMatrixAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igProjectionMatrixAttr_GetMetaObject,
        igProjectionMatrixAttr_className,
        0x4C, /* instance size */
        igProjectionMatrixAttr_GetVTable,
        &igProjectionMatrixAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
