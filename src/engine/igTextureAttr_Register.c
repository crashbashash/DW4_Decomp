extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igTextureAttr_GetVTable[];
extern char thunk_igTextureAttr_GetMetaObject[];
extern char g_igTextureAttr_callbackList[];
extern char igTextureAttr_className[];
extern char g_igTextureAttr_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igTextureAttr_InitFields();

void igTextureAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igTextureAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igTextureAttr_GetMetaObject,
        igTextureAttr_className,
        0x48, /* instance size */
        igTextureAttr_GetVTable,
        &igTextureAttr_InitFields,
        0, /* extra callback item */
        g_igTextureAttr_callbackList /* callback list */
    );
}
