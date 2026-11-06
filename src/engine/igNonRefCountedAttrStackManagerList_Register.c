extern char igNonRefCountedObjectList_GetPublishedMetaObject[];
extern char igNonRefCountedAttrStackManagerList_GetVTable[];
extern char thunk_igNonRefCountedAttrStackManagerList_GetMetaObject[];
extern char igNonRefCountedObjectList_Register[];
extern char g_igNonRefCountedAttrStackManagerList_callbackList[];
extern char igNonRefCountedAttrStackManagerList_className[];
extern char g_igNonRefCountedAttrStackManagerList_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igNonRefCountedAttrStackManagerList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igNonRefCountedAttrStackManagerList_metaObject,
        igNonRefCountedObjectList_Register,
        igNonRefCountedObjectList_GetPublishedMetaObject,
        thunk_igNonRefCountedAttrStackManagerList_GetMetaObject,
        igNonRefCountedAttrStackManagerList_className,
        0x14, /* instance size */
        igNonRefCountedAttrStackManagerList_GetVTable,
        0,
        0, /* extra callback item */
        g_igNonRefCountedAttrStackManagerList_callbackList /* callback list */
    );
}
