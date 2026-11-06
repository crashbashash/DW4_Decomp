extern char igObjectList_GetPublishedMetaObject[];
extern char igGeometryAttrList_GetVTable[];
extern char thunk_igGeometryAttrList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igGeometryAttrList_callbackList[];
extern char igGeometryAttrList_className[];
extern char g_igGeometryAttrList_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igGeometryAttrList_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igGeometryAttrList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igGeometryAttrList_GetMetaObject,
        igGeometryAttrList_className,
        0x14, /* instance size */
        igGeometryAttrList_GetVTable,
        0,
        0, /* extra callback item */
        g_igGeometryAttrList_callbackList /* callback list */
    );
}
