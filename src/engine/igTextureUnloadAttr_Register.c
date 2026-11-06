extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igTextureUnloadAttr_GetVTable[];
extern char thunk_igTextureUnloadAttr_GetMetaObject[];
extern char g_igTextureUnloadAttr_callbackList[];
extern char igTextureUnloadAttr_className[];
extern char g_igTextureUnloadAttr_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igTextureUnloadAttr_InitFields();

void igTextureUnloadAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igTextureUnloadAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igTextureUnloadAttr_GetMetaObject,
        igTextureUnloadAttr_className,
        0x14, /* instance size */
        igTextureUnloadAttr_GetVTable,
        &igTextureUnloadAttr_InitFields,
        0, /* extra callback item */
        g_igTextureUnloadAttr_callbackList /* callback list */
    );
}
