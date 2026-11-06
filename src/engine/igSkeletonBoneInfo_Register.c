/* 0x00198a50 igSkeletonBoneInfo_Register: registers class igSkeletonBoneInfo with the object system, derived from igNamedObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
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
        0,                                             /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igSkeletonBoneInfo_metaObject,      /* published MetaObject slot */
        igNamedObject_Register,                        /* base class registrar */
        igNamedObject_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igSkeletonBoneInfo_GetMetaObject_00198ac0,                                  /* own MetaObject accessor (stored at +0x54) */
        igSkeletonBoneInfo_className,       /* class name */
        0x18,                                          /* instance size */
        igSkeletonBoneInfo_GetVTable,                  /* vtable getter */
        &igSkeletonBoneInfo_InitFields,                /* field adder */
        0,                                             /* extra callback item */
        0                                              /* callback list */
    );
}
