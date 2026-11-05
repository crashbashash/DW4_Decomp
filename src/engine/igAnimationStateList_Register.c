/* 0x001a6a10 igAnimationStateList_Register: registers class igAnimationStateList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igAnimationStateList_GetVTable[];
extern char thunk_igAnimationStateList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igAnimationStateList_callbackList_0048cf08[];
extern char s_igAnimationStateList_className_004e3840[];
extern char g_igAnimationStateList_metaObject_005620e0[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();

void igAnimationStateList_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                          /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igAnimationStateList_metaObject_005620e0, /* published MetaObject slot */
        igObjectList_Register,                      /* base class registrar */
        igObjectList_GetPublishedMetaObject,        /* base class MetaObject accessor */
        thunk_igAnimationStateList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igAnimationStateList_className_004e3840,  /* class name */
        0x14,                                       /* instance size */
        igAnimationStateList_GetVTable,             /* vtable getter */
        0,                                          /* field adder */
        0,                                          /* extra callback item */
        g_igAnimationStateList_callbackList_0048cf08  /* callback list */
    );
}
