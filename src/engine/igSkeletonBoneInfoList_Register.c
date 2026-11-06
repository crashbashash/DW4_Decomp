extern char igObjectList_GetPublishedMetaObject[];
extern char igSkeletonBoneInfoList_GetVTable[];
extern char thunk_igSkeletonBoneInfoList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igSkeletonBoneInfoList_callbackList[];
extern char igSkeletonBoneInfoList_className[];
extern char g_igSkeletonBoneInfoList_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igSkeletonBoneInfoList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igSkeletonBoneInfoList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igSkeletonBoneInfoList_GetMetaObject,
        igSkeletonBoneInfoList_className,
        0x14, /* instance size */
        igSkeletonBoneInfoList_GetVTable,
        0,
        0, /* extra callback item */
        g_igSkeletonBoneInfoList_callbackList /* callback list */
    );
}
