/* 0x001a8030 igAnimationCombinerBoneInfoList_Register: registers class igAnimationCombinerBoneInfoList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igAnimationCombinerBoneInfoList_GetVTable[];
extern char thunk_igAnimationCombinerBoneInfoList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igAnimationCombinerBoneInfoList_callbackList_0048d2a8[];
extern char s_igAnimationCombinerBoneInfoList_className_004e3d80[];
extern char g_igAnimationCombinerBoneInfoList_metaObject_00562260[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();

void igAnimationCombinerBoneInfoList_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igAnimationCombinerBoneInfoList_metaObject_00562260, /* published MetaObject slot */
        igObjectList_Register,                                 /* base class registrar */
        igObjectList_GetPublishedMetaObject,                   /* base class MetaObject accessor */
        thunk_igAnimationCombinerBoneInfoList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igAnimationCombinerBoneInfoList_className_004e3d80,  /* class name */
        0x14,                                                  /* instance size */
        igAnimationCombinerBoneInfoList_GetVTable,             /* vtable getter */
        0,                                                     /* field adder */
        0,                                                     /* extra callback item */
        g_igAnimationCombinerBoneInfoList_callbackList_0048d2a8  /* callback list */
    );
}
