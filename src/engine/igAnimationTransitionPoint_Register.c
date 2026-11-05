/* 0x001a9a90 igAnimationTransitionPoint_Register: registers class igAnimationTransitionPoint with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igAnimationTransitionPoint_GetVTable[];
extern char thunk_igAnimationTransitionPoint_GetMetaObject[];
extern char igObject_Register[];
extern char g_igAnimationTransitionPoint_callbackList_0048d5f8[];
extern char s_igAnimationTransitionPoint_className_004e4220[];
extern char g_igAnimationTransitionPoint_metaObject_005623e8[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();
int igAnimationTransitionPoint_InitFields();

void igAnimationTransitionPoint_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                                /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igAnimationTransitionPoint_metaObject_005623e8, /* published MetaObject slot */
        igObject_Register,                                /* base class registrar */
        igObject_GetMetaObject_ParentAccessor,            /* base class MetaObject accessor */
        thunk_igAnimationTransitionPoint_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igAnimationTransitionPoint_className_004e4220,  /* class name */
        0x18,                                             /* instance size */
        igAnimationTransitionPoint_GetVTable,             /* vtable getter */
        &igAnimationTransitionPoint_InitFields,           /* field adder */
        0,                                                /* extra callback item */
        g_igAnimationTransitionPoint_callbackList_0048d5f8  /* callback list */
    );
}
