extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igDepthWriteStateAttr_GetVTable[];
extern char thunk_igDepthWriteStateAttr_GetMetaObject[];
extern char igDepthWriteStateAttr_className[];
extern char g_igDepthWriteStateAttr_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igDepthWriteStateAttr_InitFields();

void igDepthWriteStateAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igDepthWriteStateAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igDepthWriteStateAttr_GetMetaObject,
        igDepthWriteStateAttr_className,
        0x10, /* instance size */
        igDepthWriteStateAttr_GetVTable,
        &igDepthWriteStateAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
