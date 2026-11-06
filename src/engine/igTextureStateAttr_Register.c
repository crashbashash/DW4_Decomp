extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igTextureStateAttr_GetVTable[];
extern char thunk_igTextureStateAttr_GetMetaObject[];
extern char igTextureStateAttr_className[];
extern char g_igTextureStateAttr_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igTextureStateAttr_InitFields();

void igTextureStateAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igTextureStateAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igTextureStateAttr_GetMetaObject,
        igTextureStateAttr_className,
        0x14, /* instance size */
        igTextureStateAttr_GetVTable,
        &igTextureStateAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
