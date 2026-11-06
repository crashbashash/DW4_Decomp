extern char igNonRefCountedObjectList_GetPublishedMetaObject[];
extern char igNonRefCountedNodeList_GetVTable[];
extern char thunk_igNonRefCountedNodeList_GetMetaObject[];
extern char igNonRefCountedObjectList_Register[];
extern char g_igNonRefCountedNodeList_callbackList[];
extern char igNonRefCountedNodeList_className[];
extern char g_igNonRefCountedNodeList_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igNonRefCountedNodeList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igNonRefCountedNodeList_metaObject,
        igNonRefCountedObjectList_Register,
        igNonRefCountedObjectList_GetPublishedMetaObject,
        thunk_igNonRefCountedNodeList_GetMetaObject,
        igNonRefCountedNodeList_className,
        0x14, /* instance size */
        igNonRefCountedNodeList_GetVTable,
        0,
        0, /* extra callback item */
        g_igNonRefCountedNodeList_callbackList /* callback list */
    );
}
