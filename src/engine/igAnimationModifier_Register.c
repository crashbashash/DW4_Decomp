/* 0x001a7610 igAnimationModifier_Register: registers class igAnimationModifier with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igAnimationModifier_GetVTable[];
extern char thunk_igAnimationModifier_GetMetaObject[];
extern char igObject_Register[];
extern char g_igAnimationModifier_callbackList_0048d1b0[];
extern char s_igAnimationModifier_className_004e3c90[];
extern char g_igAnimationModifier_metaObject_00562200[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();
int igAnimationModifier_InitFields();

void igAnimationModifier_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                         /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igAnimationModifier_metaObject_00562200, /* published MetaObject slot */
        igObject_Register,                         /* base class registrar */
        igObject_GetMetaObject_ParentAccessor,     /* base class MetaObject accessor */
        thunk_igAnimationModifier_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igAnimationModifier_className_004e3c90,  /* class name */
        0x14,                                      /* instance size */
        igAnimationModifier_GetVTable,             /* vtable getter */
        &igAnimationModifier_InitFields,           /* field adder */
        0,                                         /* extra callback item */
        g_igAnimationModifier_callbackList_0048d1b0  /* callback list */
    );
}
