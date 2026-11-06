/* 0x001a9ca0 igAnimationTransitionParams_Register: registers class igAnimationTransitionParams with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igAnimationTransitionParams_GetVTable[];
extern char thunk_igAnimationTransitionParams_GetMetaObject[];
extern char igObject_Register[];
extern char igAnimationTransitionParams_className[];
extern char g_igAnimationTransitionParams_metaObject[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();
int igAnimationTransitionParams_InitFields();

void igAnimationTransitionParams_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igAnimationTransitionParams_metaObject, /* published MetaObject slot */
        igObject_Register,                                 /* base class registrar */
        igObject_GetMetaObject_ParentAccessor,             /* base class MetaObject accessor */
        thunk_igAnimationTransitionParams_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igAnimationTransitionParams_className,  /* class name */
        0x20,                                              /* instance size */
        igAnimationTransitionParams_GetVTable,             /* vtable getter */
        &igAnimationTransitionParams_InitFields,           /* field adder */
        0,                                                 /* extra callback item */
        0                                                  /* callback list */
    );
}
