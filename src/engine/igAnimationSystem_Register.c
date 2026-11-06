/* 0x001a66b0 igAnimationSystem_Register: registers class igAnimationSystem with the object system, derived from igNamedObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igNamedObject_GetPublishedMetaObject[];
extern char thunk_igAnimationSystem_GetMetaObject[];
extern char igNamedObject_Register[];
extern char g_igAnimationSystem_callbackList[];
extern char igAnimationSystem_className[];
extern char g_igAnimationSystem_metaObject[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();
int igAnimationSystem_InitFields();

void igAnimationSystem_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        1,                                             /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igAnimationSystem_metaObject,       /* published MetaObject slot */
        igNamedObject_Register,                        /* base class registrar */
        igNamedObject_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igAnimationSystem_GetMetaObject,         /* own MetaObject accessor (stored at +0x54) */
        igAnimationSystem_className,        /* class name */
        0x10,                                          /* instance size */
        0,                                             /* vtable getter */
        &igAnimationSystem_InitFields,                 /* field adder */
        0,                                             /* extra callback item */
        g_igAnimationSystem_callbackList      /* callback list */
    );
}
