extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igTextureBindAttr_GetVTable[];
extern char thunk_igTextureBindAttr_GetMetaObject[];
extern char g_igTextureBindAttr_callbackList[];
extern char igTextureBindAttr_className[];
extern char g_igTextureBindAttr_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
extern int thunk_FUN_00140f40[4];
int igTextureBindAttr_InitFields();

void igTextureBindAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igTextureBindAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igTextureBindAttr_GetMetaObject,
        igTextureBindAttr_className,
        0x14, /* instance size */
        igTextureBindAttr_GetVTable,
        &igTextureBindAttr_InitFields,
        thunk_FUN_00140f40, /* extra callback item */
        g_igTextureBindAttr_callbackList /* callback list */
    );
}
