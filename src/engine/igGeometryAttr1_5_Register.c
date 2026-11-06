extern char igGeometryAttr1_5_GetVTable[];
extern char thunk_igGeometryAttr1_5_GetMetaObject[];
extern char igGeometryAttr_GetPublishedMetaObject[];
extern char igGeometryAttr_Register[];
extern char g_igGeometryAttr1_5_callbackList[];
extern char igGeometryAttr1_5_className[];
extern char g_igGeometryAttr1_5_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igGeometryAttr1_5_InitFields();

void igGeometryAttr1_5_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igGeometryAttr1_5_metaObject,
        igGeometryAttr_Register,
        igGeometryAttr_GetPublishedMetaObject,
        thunk_igGeometryAttr1_5_GetMetaObject,
        igGeometryAttr1_5_className,
        0x34, /* instance size */
        igGeometryAttr1_5_GetVTable,
        &igGeometryAttr1_5_InitFields,
        0, /* extra callback item */
        g_igGeometryAttr1_5_callbackList /* callback list */
    );
}
