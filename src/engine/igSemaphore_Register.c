/* 0x002ba740 igSemaphore_Register: registers class igSemaphore with the object system, derived from igNamedObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igNamedObject_GetPublishedMetaObject[];
extern char thunk_igSemaphore_GetMetaObject[];
extern char igNamedObject_Register[];
extern char igSemaphore_className[];
extern char g_igSemaphore_metaObject[];
/* Run-once guard shared by the registrars: sets a gp-relative flag byte (asm/FUN_002b5d50.s). */
int FUN_002b5d50();
int igMetaObject_RegisterClass();
/* Code in the gap after this function: the class's no-argument field adder (10th registration argument). */
extern int igSemaphore_InitFields_002ba7c0[4];
void igSemaphore_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        1,                                             /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igSemaphore_metaObject,             /* published MetaObject slot */
        igNamedObject_Register,                        /* base class registrar */
        igNamedObject_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igSemaphore_GetMetaObject,               /* own MetaObject accessor (stored at +0x54) */
        igSemaphore_className,              /* class name */
        0xC,                                           /* instance size */
        0,                                             /* vtable getter */
        &igSemaphore_InitFields_002ba7c0[0],           /* field adder */
        0,                                             /* extra callback item */
        0                                              /* callback list */
    );
}
