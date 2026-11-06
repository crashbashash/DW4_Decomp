extern char igObjectList_GetPublishedMetaObject[];
extern char igGeometryList_GetVTable[];
extern char thunk_igGeometryList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igGeometryList_callbackList[];
extern char igGeometryList_className[];
extern char g_igGeometryList_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igGeometryList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igGeometryList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igGeometryList_GetMetaObject,
        igGeometryList_className,
        0x14, /* instance size */
        igGeometryList_GetVTable,
        0,
        0, /* extra callback item */
        g_igGeometryList_callbackList /* callback list */
    );
}
