/* 0x001a9920 igAnimationTransitionPointList_Register: registers class igAnimationTransitionPointList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igAnimationTransitionPointList_GetVTable[];
extern char thunk_igAnimationTransitionPointList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igAnimationTransitionPointList_callbackList_0048d5f0[];
extern char s_igAnimationTransitionPointList_className_004e4200[];
extern char g_igAnimationTransitionPointList_metaObject_005623e0[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();

void igAnimationTransitionPointList_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                                    /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igAnimationTransitionPointList_metaObject_005623e0, /* published MetaObject slot */
        igObjectList_Register,                                /* base class registrar */
        igObjectList_GetPublishedMetaObject,                  /* base class MetaObject accessor */
        thunk_igAnimationTransitionPointList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igAnimationTransitionPointList_className_004e4200,  /* class name */
        0x14,                                                 /* instance size */
        igAnimationTransitionPointList_GetVTable,             /* vtable getter */
        0,                                                    /* field adder */
        0,                                                    /* extra callback item */
        g_igAnimationTransitionPointList_callbackList_0048d5f0  /* callback list */
    );
}
