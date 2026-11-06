extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igGeometryMaskAttr_GetVTable[];
extern char thunk_igGeometryMaskAttr_GetMetaObject[];
extern char igGeometryMaskAttr_className[];
extern char g_igGeometryMaskAttr_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igGeometryMaskAttr_InitFields();

void igGeometryMaskAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igGeometryMaskAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igGeometryMaskAttr_GetMetaObject,
        igGeometryMaskAttr_className,
        0x10, /* instance size */
        igGeometryMaskAttr_GetVTable,
        &igGeometryMaskAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
