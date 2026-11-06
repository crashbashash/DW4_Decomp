extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igDepthStateAttr_GetVTable[];
extern char thunk_igDepthStateAttr_GetMetaObject[];
extern char igDepthStateAttr_className[];
extern char g_igDepthStateAttr_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igDepthStateAttr_InitFields();

void igDepthStateAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igDepthStateAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igDepthStateAttr_GetMetaObject,
        igDepthStateAttr_className,
        0x10, /* instance size */
        igDepthStateAttr_GetVTable,
        &igDepthStateAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
