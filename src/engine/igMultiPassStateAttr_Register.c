extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igMultiPassStateAttr_GetVTable[];
extern char thunk_igMultiPassStateAttr_GetMetaObject[];
extern char igMultiPassStateAttr_className[];
extern char g_igMultiPassStateAttr_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igMultiPassStateAttr_InitFields();

void igMultiPassStateAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMultiPassStateAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igMultiPassStateAttr_GetMetaObject,
        igMultiPassStateAttr_className,
        0x10, /* instance size */
        igMultiPassStateAttr_GetVTable,
        &igMultiPassStateAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
