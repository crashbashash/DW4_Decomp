/* 0x0014bbc0 igUserUCodeExt_Register: registers class igUserUCodeExt with the object system, derived from igContextExt.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char thunk_igUserUCodeExt_GetMetaObject[];
extern char igContextExt_GetPublishedMetaObject_0014bc40[];
extern char igContextExt_Register[];
extern char s_igUserUCodeExt_className_004dbe88[];
extern char g_igUserUCodeExt_metaObject_0055faf0[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
void FUN_0014bc50(void);  /* code at 0x14bc50, passed by address (was DAT_14bc50; docs/engine/function-inventory.md) */
void igUserUCodeExt_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        1,                                            /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igUserUCodeExt_metaObject_0055faf0,         /* published MetaObject slot */
        igContextExt_Register,                        /* base class registrar */
        igContextExt_GetPublishedMetaObject_0014bc40, /* base class MetaObject accessor */
        thunk_igUserUCodeExt_GetMetaObject,           /* own MetaObject accessor (stored at +0x54) */
        s_igUserUCodeExt_className_004dbe88,          /* class name */
        0x14,                                         /* instance size */
        0,                                            /* vtable getter */
        FUN_0014bc50,                             /* field adder */
        0,                                            /* extra callback item */
        0                                             /* callback list */
    );
}
