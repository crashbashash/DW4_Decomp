extern char igObjectList_GetPublishedMetaObject[];
extern char igAnimationCombinerBoneInfoList_GetVTable[];
extern char thunk_igAnimationCombinerBoneInfoList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igAnimationCombinerBoneInfoList_callbackList[];
extern char igAnimationCombinerBoneInfoList_className[];
extern char g_igAnimationCombinerBoneInfoList_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igAnimationCombinerBoneInfoList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igAnimationCombinerBoneInfoList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igAnimationCombinerBoneInfoList_GetMetaObject,
        igAnimationCombinerBoneInfoList_className,
        0x14, /* instance size */
        igAnimationCombinerBoneInfoList_GetVTable,
        0,
        0, /* extra callback item */
        g_igAnimationCombinerBoneInfoList_callbackList /* callback list */
    );
}
