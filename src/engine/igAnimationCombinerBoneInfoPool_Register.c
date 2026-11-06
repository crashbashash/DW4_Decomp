extern char igObjectPool_Register[];
extern char igObjectPool_GetPublishedMetaObject[];
extern char igAnimationCombinerBoneInfoPool_GetVTable[];
extern char thunk_igAnimationCombinerBoneInfoPool_GetMetaObject[];
extern char g_igAnimationCombinerBoneInfoPool_callbackList[];
extern char igAnimationCombinerBoneInfoPool_className[];
extern char g_igAnimationCombinerBoneInfoPool_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igAnimationCombinerBoneInfoPool_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igAnimationCombinerBoneInfoPool_metaObject,
        igObjectPool_Register,
        igObjectPool_GetPublishedMetaObject,
        thunk_igAnimationCombinerBoneInfoPool_GetMetaObject,
        igAnimationCombinerBoneInfoPool_className,
        0x20, /* instance size */
        igAnimationCombinerBoneInfoPool_GetVTable,
        0,
        0, /* extra callback item */
        g_igAnimationCombinerBoneInfoPool_callbackList /* callback list */
    );
}
