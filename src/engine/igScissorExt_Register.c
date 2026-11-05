/* 0x0014bd30 igScissorExt_Register: registers class igScissorExt with the object system, derived from igContextExt.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igContextExt_GetPublishedMetaObject_0014bc40[];
extern char thunk_igScissorExt_GetMetaObject[];
extern char igContextExt_Register[];
extern char s_igScissorExt_className_004dbe98[];
extern char g_igScissorExt_metaObject_0055faf8[];
/* Run-once guard shared by the registrars: sets a gp-relative flag byte (asm/FUN_00149bc0.s). */
int FUN_00149bc0();
int igMetaObject_RegisterClass();
/* Code in the gap after this function: the class's no-argument field adder (10th registration argument). */
extern int igScissorExt_InitFields_0014bdb0[4];
void igScissorExt_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        1,                                            /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igScissorExt_metaObject_0055faf8,           /* published MetaObject slot */
        igContextExt_Register,                        /* base class registrar */
        igContextExt_GetPublishedMetaObject_0014bc40, /* base class MetaObject accessor */
        thunk_igScissorExt_GetMetaObject,             /* own MetaObject accessor (stored at +0x54) */
        s_igScissorExt_className_004dbe98,            /* class name */
        0x14,                                         /* instance size */
        0,                                            /* vtable getter */
        &igScissorExt_InitFields_0014bdb0[0],         /* field adder */
        0,                                            /* extra callback item */
        0                                             /* callback list */
    );
}
