/* 0x001a8810 igAnimationCombiner_Register: registers class igAnimationCombiner with the object system, derived from igAnimationSystem.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igAnimationSystem_Register[];
extern char igAnimationCombiner_GetVTable[];
void thunk_FUN_001a8520(void);  /* code at 0x1a8890, passed by address (was DAT_1a8890; docs/engine/function-inventory.md) */
extern char igAnimationSystem_GetPublishedMetaObject_001a88a0[];
extern char g_igAnimationCombiner_callbackList_0048d350[];
extern char s_igAnimationCombiner_className_004e3ea0[];
extern char g_igAnimationCombiner_metaObject_005622b8[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();
extern int thunk_FUN_001abca0[4];
int igAnimationCombiner_InitFields();

void igAnimationCombiner_Register(void) {
    GpFlag_SetOnce_00194380();  /* shared set-once latch run before every registration of this family (asm/GpFlag_SetOnce_00194380.s) */
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igAnimationCombiner_metaObject_005622b8,         /* published MetaObject slot */
        igAnimationSystem_Register,                        /* base class registrar */
        igAnimationSystem_GetPublishedMetaObject_001a88a0, /* base class MetaObject accessor */
        thunk_FUN_001a8520,                                      /* own MetaObject accessor (stored at +0x54) */
        s_igAnimationCombiner_className_004e3ea0,          /* class name */
        0x60,                                              /* instance size */
        igAnimationCombiner_GetVTable,                     /* vtable getter */
        &igAnimationCombiner_InitFields,                   /* field adder */
        thunk_FUN_001abca0,                                /* static-initializer callback item (appended on fresh configuration) */
        g_igAnimationCombiner_callbackList_0048d350        /* 0-terminated dependency-callback list */
    );
}
