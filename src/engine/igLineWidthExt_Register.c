/* 0x0014d6e0 igLineWidthExt_Register: registers class igLineWidthExt with the object system, derived from igContextExt.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igContextExt_GetPublishedMetaObject_0014bc40[];
extern char thunk_igLineWidthExt_GetMetaObject_0014d750[];
extern char igContextExt_Register[];
extern char s_igLineWidthExt_className_004dc7f8[];
extern char g_igLineWidthExt_metaObject_0055fd18[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
int igLineWidthExt_InitFields();

void igLineWidthExt_Register(void) {
    /* Once-only static-init guard for this unit: the first call sets a gp-relative flag byte and
     * (in some units) chains the RunStaticInit thunks of related classes; per its asm, not a registrar. */
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        1,                                            /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igLineWidthExt_metaObject_0055fd18,         /* published MetaObject slot */
        igContextExt_Register,                        /* base class registrar */
        igContextExt_GetPublishedMetaObject_0014bc40, /* base class MetaObject accessor */
        thunk_igLineWidthExt_GetMetaObject_0014d750,  /* own MetaObject accessor (stored at +0x54) */
        s_igLineWidthExt_className_004dc7f8,          /* class name */
        0x18,                                         /* instance size */
        0,                                            /* vtable getter */
        &igLineWidthExt_InitFields,                   /* field adder */
        0,                                            /* extra callback item */
        0                                             /* callback list */
    );
}
