extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igTextureCoordSourceAttr_GetVTable[];
extern char thunk_igTextureCoordSourceAttr_GetMetaObject[];
extern char igTextureCoordSourceAttr_className[];
extern char g_igTextureCoordSourceAttr_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igTextureCoordSourceAttr_InitFields();

void igTextureCoordSourceAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igTextureCoordSourceAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igTextureCoordSourceAttr_GetMetaObject,
        igTextureCoordSourceAttr_className,
        0x18, /* instance size */
        igTextureCoordSourceAttr_GetVTable,
        &igTextureCoordSourceAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
