extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igBlendStateAttr_GetVTable[];
extern char thunk_igBlendStateAttr_GetMetaObject[];
extern char igBlendStateAttr_className[];
extern char g_igBlendStateAttr_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igBlendStateAttr_InitFields();

void igBlendStateAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igBlendStateAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igBlendStateAttr_GetMetaObject,
        igBlendStateAttr_className,
        0x10, /* instance size */
        igBlendStateAttr_GetVTable,
        &igBlendStateAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
