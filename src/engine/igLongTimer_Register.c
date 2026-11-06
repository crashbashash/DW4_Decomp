/* 0x002c18c0 igLongTimer_Register: registers class igLongTimer with the object system, derived from igTimer.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igTimer_Register[];
extern char thunk_igLongTimer_GetMetaObject_002b7b60[];
extern char igTimer_GetPublishedMetaObject[];
extern char igLongTimer_className[];
extern char g_igLongTimer_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igLongTimer_InitFields();

void igLongTimer_Register(void) {
    /* Once-only static-init guard for this unit: the first call sets a gp-relative flag byte and
     * (in some units) chains the RunStaticInit thunks of related classes; per its asm, not a registrar. */
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        1,                                        /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igLongTimer_metaObject,        /* published MetaObject slot */
        igTimer_Register,                         /* base class registrar */
        igTimer_GetPublishedMetaObject,  /* base class MetaObject accessor */
        thunk_igLongTimer_GetMetaObject_002b7b60, /* own MetaObject accessor (stored at +0x54) */
        igLongTimer_className,         /* class name */
        0x28,                                     /* instance size */
        0,                                        /* vtable getter */
        &igLongTimer_InitFields,                  /* field adder */
        0,                                        /* extra callback item */
        0                                         /* callback list */
    );
}
