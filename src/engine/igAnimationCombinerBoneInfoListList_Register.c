/* 0x001a7f10 igAnimationCombinerBoneInfoListList_Register: registers class igAnimationCombinerBoneInfoListList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igAnimationCombinerBoneInfoListList_GetVTable[];
extern char thunk_igAnimationCombinerBoneInfoListList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igAnimationCombinerBoneInfoListList_callbackList_0048d2a0[];
extern char s_igAnimationCombinerBoneInfoListList_className_004e3d50[];
extern char g_igAnimationCombinerBoneInfoListList_metaObject_00562258[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();

void igAnimationCombinerBoneInfoListList_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                                         /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igAnimationCombinerBoneInfoListList_metaObject_00562258, /* published MetaObject slot */
        igObjectList_Register,                                     /* base class registrar */
        igObjectList_GetPublishedMetaObject,                       /* base class MetaObject accessor */
        thunk_igAnimationCombinerBoneInfoListList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igAnimationCombinerBoneInfoListList_className_004e3d50,  /* class name */
        0x14,                                                      /* instance size */
        igAnimationCombinerBoneInfoListList_GetVTable,             /* vtable getter */
        0,                                                         /* field adder */
        0,                                                         /* extra callback item */
        g_igAnimationCombinerBoneInfoListList_callbackList_0048d2a0  /* callback list */
    );
}
