extern char igNamedObject_GetPublishedMetaObject[];
extern char igSkeletonBoneInfo_GetVTable[];
extern char thunk_igSkeletonBoneInfo_GetMetaObject_00198ac0[];
extern char igNamedObject_Register[];
extern char igSkeletonBoneInfo_className[];
extern char g_igSkeletonBoneInfo_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igSkeletonBoneInfo_InitFields();

void igSkeletonBoneInfo_Register(void) {
    SceneGraphLibrary_MarkRegistered();  /* one-shot static-init latch (sets a gp-relative byte flag once) */
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igSkeletonBoneInfo_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        thunk_igSkeletonBoneInfo_GetMetaObject_00198ac0,
        igSkeletonBoneInfo_className,
        0x18, /* instance size */
        igSkeletonBoneInfo_GetVTable,
        &igSkeletonBoneInfo_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
