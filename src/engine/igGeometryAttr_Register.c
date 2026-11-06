extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char thunk_igGeometryAttr_GetMetaObject[];
extern char g_igGeometryAttr_callbackList[];
extern char igGeometryAttr_className[];
extern char g_igGeometryAttr_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igGeometryAttr_InitFields();

void igGeometryAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igGeometryAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igGeometryAttr_GetMetaObject,
        igGeometryAttr_className,
        0x30, /* instance size */
        0,
        &igGeometryAttr_InitFields,
        0, /* extra callback item */
        g_igGeometryAttr_callbackList /* callback list */
    );
}
