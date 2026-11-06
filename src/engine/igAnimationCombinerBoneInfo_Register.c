extern char igObject_GetMetaObject_ParentAccessor[];
extern char igAnimationCombinerBoneInfo_GetVTable[];
extern char thunk_igAnimationCombinerBoneInfo_GetMetaObject[];
extern char igObject_Register[];
extern char g_igAnimationCombinerBoneInfo_callbackList[];
extern char igAnimationCombinerBoneInfo_className[];
extern char g_igAnimationCombinerBoneInfo_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igAnimationCombinerBoneInfo_InitFields();

void igAnimationCombinerBoneInfo_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igAnimationCombinerBoneInfo_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igAnimationCombinerBoneInfo_GetMetaObject,
        igAnimationCombinerBoneInfo_className,
        0x3C, /* instance size */
        igAnimationCombinerBoneInfo_GetVTable,
        &igAnimationCombinerBoneInfo_InitFields,
        0, /* extra callback item */
        g_igAnimationCombinerBoneInfo_callbackList /* callback list */
    );
}
