extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igColorMaskAttr_GetVTable[];
extern char thunk_igColorMaskAttr_GetMetaObject[];
extern char igColorMaskAttr_className[];
extern char g_igColorMaskAttr_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igColorMaskAttr_InitFields();

void igColorMaskAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igColorMaskAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igColorMaskAttr_GetMetaObject,
        igColorMaskAttr_className,
        0x14, /* instance size */
        igColorMaskAttr_GetVTable,
        &igColorMaskAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
