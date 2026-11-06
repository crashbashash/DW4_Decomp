extern char igObjectList_GetPublishedMetaObject[];
extern char igAnimationCombinerBoneInfoListList_GetVTable[];
extern char thunk_igAnimationCombinerBoneInfoListList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igAnimationCombinerBoneInfoListList_callbackList[];
extern char igAnimationCombinerBoneInfoListList_className[];
extern char g_igAnimationCombinerBoneInfoListList_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igAnimationCombinerBoneInfoListList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igAnimationCombinerBoneInfoListList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igAnimationCombinerBoneInfoListList_GetMetaObject,
        igAnimationCombinerBoneInfoListList_className,
        0x14, /* instance size */
        igAnimationCombinerBoneInfoListList_GetVTable,
        0,
        0, /* extra callback item */
        g_igAnimationCombinerBoneInfoListList_callbackList /* callback list */
    );
}
