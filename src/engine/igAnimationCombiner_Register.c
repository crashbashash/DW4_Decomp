/* 0x001a8810 igAnimationCombiner_Register: registers class igAnimationCombiner with the object system, derived from igAnimationSystem.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igAnimationSystem_Register[];
extern char igAnimationCombiner_GetVTable[];
void thunk_FUN_001a8520(void);
extern char igAnimationSystem_GetPublishedMetaObject[];
extern char g_igAnimationCombiner_callbackList[];
extern char igAnimationCombiner_className[];
extern char g_igAnimationCombiner_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
extern int thunk_FUN_001abca0[4];
int igAnimationCombiner_InitFields();

void igAnimationCombiner_Register(void) {
    SceneGraphLibrary_MarkRegistered();  /* shared set-once latch run before every registration of this family (asm/SceneGraphLibrary_MarkRegistered.s) */
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igAnimationCombiner_metaObject,         /* published MetaObject slot */
        igAnimationSystem_Register,                        /* base class registrar */
        igAnimationSystem_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_FUN_001a8520,                                      /* own MetaObject accessor (stored at +0x54) */
        igAnimationCombiner_className,          /* class name */
        0x60,                                              /* instance size */
        igAnimationCombiner_GetVTable,                     /* vtable getter */
        &igAnimationCombiner_InitFields,                   /* field adder */
        thunk_FUN_001abca0,                                /* static-initializer callback item (appended on fresh configuration) */
        g_igAnimationCombiner_callbackList        /* 0-terminated dependency-callback list */
    );
}
