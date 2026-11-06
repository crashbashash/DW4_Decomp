extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igShadeModelAttr_GetVTable[];
extern char thunk_igShadeModelAttr_GetMetaObject[];
extern char igShadeModelAttr_className[];
extern char g_igShadeModelAttr_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igShadeModelAttr_InitFields();

void igShadeModelAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igShadeModelAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igShadeModelAttr_GetMetaObject,
        igShadeModelAttr_className,
        0x10, /* instance size */
        igShadeModelAttr_GetVTable,
        &igShadeModelAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
