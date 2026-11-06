/* 0x0014f930 igDecalExt_Register: registers class igDecalExt with the object system, derived from igContextExt.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igContextExt_GetPublishedMetaObject[];
void thunk_FUN_0014f8d0(void);  /* code at 0x14f9a0, passed by address (was DAT_14f9a0; docs/engine/function-inventory.md) */
extern char igContextExt_Register[];
extern char igDecalExt_className[];
extern char g_igDecalExt_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
int igDecalExt_InitFields();

void igDecalExt_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        1,                                            /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igDecalExt_metaObject,             /* published MetaObject slot */
        igContextExt_Register,                        /* base class registrar */
        igContextExt_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_FUN_0014f8d0,                                 /* own MetaObject accessor (stored at +0x54) */
        igDecalExt_className,              /* class name */
        0x18,                                         /* instance size */
        0,                                            /* vtable getter */
        &igDecalExt_InitFields,                       /* field adder */
        0,                                            /* extra callback item */
        0                                             /* callback list */
    );
}
