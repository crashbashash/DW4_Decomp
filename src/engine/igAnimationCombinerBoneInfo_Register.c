/* 0x001a8230 igAnimationCombinerBoneInfo_Register: registers class igAnimationCombinerBoneInfo with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igAnimationCombinerBoneInfo_GetVTable[];
extern char thunk_igAnimationCombinerBoneInfo_GetMetaObject[];
extern char igObject_Register[];
extern char g_igAnimationCombinerBoneInfo_callbackList_0048d2b0[];
extern char s_igAnimationCombinerBoneInfo_className_004e3da0[];
extern char g_igAnimationCombinerBoneInfo_metaObject_00562268[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();
int igAnimationCombinerBoneInfo_InitFields();

void igAnimationCombinerBoneInfo_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igAnimationCombinerBoneInfo_metaObject_00562268, /* published MetaObject slot */
        igObject_Register,                                 /* base class registrar */
        igObject_GetMetaObject_ParentAccessor,             /* base class MetaObject accessor */
        thunk_igAnimationCombinerBoneInfo_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igAnimationCombinerBoneInfo_className_004e3da0,  /* class name */
        0x3C,                                              /* instance size */
        igAnimationCombinerBoneInfo_GetVTable,             /* vtable getter */
        &igAnimationCombinerBoneInfo_InitFields,           /* field adder */
        0,                                                 /* extra callback item */
        g_igAnimationCombinerBoneInfo_callbackList_0048d2b0  /* callback list */
    );
}
