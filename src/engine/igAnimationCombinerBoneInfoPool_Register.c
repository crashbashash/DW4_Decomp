/* 0x001a7da0 igAnimationCombinerBoneInfoPool_Register: registers class igAnimationCombinerBoneInfoPool with the object system, derived from igObjectPool.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectPool_Register[];
extern char igObjectPool_GetPublishedMetaObject_00197aa0[];
extern char igAnimationCombinerBoneInfoPool_GetVTable[];
extern char thunk_igAnimationCombinerBoneInfoPool_GetMetaObject[];
extern char g_igAnimationCombinerBoneInfoPool_callbackList_0048d298[];
extern char s_igAnimationCombinerBoneInfoPool_className_004e3d30[];
extern char g_igAnimationCombinerBoneInfoPool_metaObject_00562250[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();

void igAnimationCombinerBoneInfoPool_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igAnimationCombinerBoneInfoPool_metaObject_00562250, /* published MetaObject slot */
        igObjectPool_Register,                                 /* base class registrar */
        igObjectPool_GetPublishedMetaObject_00197aa0,          /* base class MetaObject accessor */
        thunk_igAnimationCombinerBoneInfoPool_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igAnimationCombinerBoneInfoPool_className_004e3d30,  /* class name */
        0x20,                                                  /* instance size */
        igAnimationCombinerBoneInfoPool_GetVTable,             /* vtable getter */
        0,                                                     /* field adder */
        0,                                                     /* extra callback item */
        g_igAnimationCombinerBoneInfoPool_callbackList_0048d298  /* callback list */
    );
}
