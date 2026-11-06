extern char igNonRefCountedObjectList_GetPublishedMetaObject[];
extern char igNonRefCountedTransformList_GetVTable[];
extern char thunk_igNonRefCountedTransformList_GetMetaObject[];
extern char igNonRefCountedObjectList_Register[];
extern char g_igNonRefCountedTransformList_callbackList[];
extern char igNonRefCountedTransformList_className[];
extern char g_igNonRefCountedTransformList_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igNonRefCountedTransformList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igNonRefCountedTransformList_metaObject,
        igNonRefCountedObjectList_Register,
        igNonRefCountedObjectList_GetPublishedMetaObject,
        thunk_igNonRefCountedTransformList_GetMetaObject,
        igNonRefCountedTransformList_className,
        0x14, /* instance size */
        igNonRefCountedTransformList_GetVTable,
        0,
        0, /* extra callback item */
        g_igNonRefCountedTransformList_callbackList /* callback list */
    );
}
