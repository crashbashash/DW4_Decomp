extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igGeometrySetAttr_GetVTable[];
extern char thunk_igGeometrySetAttr_GetMetaObject[];
extern char g_igGeometrySetAttr_callbackList[];
extern char igGeometrySetAttr_className[];
extern char g_igGeometrySetAttr_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igGeometrySetAttr_InitFields();

void igGeometrySetAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igGeometrySetAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igGeometrySetAttr_GetMetaObject,
        igGeometrySetAttr_className,
        0x20, /* instance size */
        igGeometrySetAttr_GetVTable,
        &igGeometrySetAttr_InitFields,
        0, /* extra callback item */
        g_igGeometrySetAttr_callbackList /* callback list */
    );
}
