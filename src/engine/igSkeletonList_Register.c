extern char igObjectList_GetPublishedMetaObject[];
extern char igSkeletonList_GetVTable[];
extern char thunk_igSkeletonList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igSkeletonList_callbackList[];
extern char igSkeletonList_className[];
extern char g_igSkeletonList_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igSkeletonList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igSkeletonList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igSkeletonList_GetMetaObject,
        igSkeletonList_className,
        0x14, /* instance size */
        igSkeletonList_GetVTable,
        0,
        0, /* extra callback item */
        g_igSkeletonList_callbackList /* callback list */
    );
}
