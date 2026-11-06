extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igPolygonModeAttr_GetVTable[];
extern char thunk_igPolygonModeAttr_GetMetaObject[];
extern char igPolygonModeAttr_className[];
extern char g_igPolygonModeAttr_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igPolygonModeAttr_InitFields();

void igPolygonModeAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igPolygonModeAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igPolygonModeAttr_GetMetaObject,
        igPolygonModeAttr_className,
        0x10, /* instance size */
        igPolygonModeAttr_GetVTable,
        &igPolygonModeAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
