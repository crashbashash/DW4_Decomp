/* 0x001a6dd0 igAnimationState_Register: registers class igAnimationState with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igAnimationState_GetVTable[];
extern char thunk_igAnimationState_GetMetaObject[];
extern char igObject_Register[];
extern char g_igAnimationState_callbackList_0048cf88[];
extern char s_igAnimationState_className_004e3940[];
extern char g_igAnimationState_metaObject_00562100[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();
int igAnimationState_InitFields();

void igAnimationState_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                      /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igAnimationState_metaObject_00562100, /* published MetaObject slot */
        igObject_Register,                      /* base class registrar */
        igObject_GetMetaObject_ParentAccessor,  /* base class MetaObject accessor */
        thunk_igAnimationState_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igAnimationState_className_004e3940,  /* class name */
        0xA0,                                   /* instance size */
        igAnimationState_GetVTable,             /* vtable getter */
        &igAnimationState_InitFields,           /* field adder */
        0,                                      /* extra callback item */
        g_igAnimationState_callbackList_0048cf88  /* callback list */
    );
}
