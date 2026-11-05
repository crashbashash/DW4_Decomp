/* 0x001a96d0 igAnimationTransitionDefinition_Register: registers class igAnimationTransitionDefinition with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igAnimationTransitionDefinition_GetVTable[];
extern char thunk_igAnimationTransitionDefinition_GetMetaObject[];
extern char igObject_Register[];
extern char g_igAnimationTransitionDefinition_callbackList_0048d5a0[];
extern char s_igAnimationTransitionDefinition_className_004e41b0[];
extern char g_igAnimationTransitionDefinition_metaObject_005623c0[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();
int igAnimationTransitionDefinition_InitFields();

void igAnimationTransitionDefinition_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igAnimationTransitionDefinition_metaObject_005623c0, /* published MetaObject slot */
        igObject_Register,                                     /* base class registrar */
        igObject_GetMetaObject_ParentAccessor,                 /* base class MetaObject accessor */
        thunk_igAnimationTransitionDefinition_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igAnimationTransitionDefinition_className_004e41b0,  /* class name */
        0x14,                                                  /* instance size */
        igAnimationTransitionDefinition_GetVTable,             /* vtable getter */
        &igAnimationTransitionDefinition_InitFields,           /* field adder */
        0,                                                     /* extra callback item */
        g_igAnimationTransitionDefinition_callbackList_0048d5a0  /* callback list */
    );
}
