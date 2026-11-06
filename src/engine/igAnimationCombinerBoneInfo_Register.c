/* 0x001a8230 igAnimationCombinerBoneInfo_Register: registers class igAnimationCombinerBoneInfo with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
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
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igAnimationCombinerBoneInfo_metaObject, /* published MetaObject slot */
        igObject_Register,                                 /* base class registrar */
        igObject_GetMetaObject_ParentAccessor,             /* base class MetaObject accessor */
        thunk_igAnimationCombinerBoneInfo_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igAnimationCombinerBoneInfo_className,  /* class name */
        0x3C,                                              /* instance size */
        igAnimationCombinerBoneInfo_GetVTable,             /* vtable getter */
        &igAnimationCombinerBoneInfo_InitFields,           /* field adder */
        0,                                                 /* extra callback item */
        g_igAnimationCombinerBoneInfo_callbackList  /* callback list */
    );
}
