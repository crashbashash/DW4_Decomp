/* 0x002c1790 igMedia_Register: registers class igMedia with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char thunk_igMedia_GetMetaObject[];
extern char thunk_FUN_002ebcf0[];
extern char igObject_Register[];
extern char s_igMedia_className_004f6e90[];
extern char g_igMedia_metaObject_00586020[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
extern int igMedia_InitFields_002c1810[4];
void igMedia_Register(void) {
    /* Once-only static-init guard for this unit: the first call sets a gp-relative flag byte and
     * (in some units) chains the RunStaticInit thunks of related classes; per its asm, not a registrar. */
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        1,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igMedia_metaObject_00586020,         /* published MetaObject slot */
        igObject_Register,                     /* base class registrar */
        igObject_GetMetaObject_ParentAccessor, /* base class MetaObject accessor */
        thunk_igMedia_GetMetaObject,           /* own MetaObject accessor (stored at +0x54) */
        s_igMedia_className_004f6e90,          /* class name */
        8,                                     /* instance size */
        0,                                     /* vtable getter */
        &igMedia_InitFields_002c1810[0],       /* field adder */
        thunk_FUN_002ebcf0,                    /* extra callback item */
        0                                      /* callback list */
    );
}
