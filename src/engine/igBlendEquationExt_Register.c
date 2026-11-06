/* 0x0014ff10 igBlendEquationExt_Register: registers class igBlendEquationExt with the object system, derived from igContextExt.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igContextExt_GetPublishedMetaObject[];
extern char thunk_igBlendEquationExt_GetMetaObject[];
extern char igContextExt_Register[];
extern char igBlendEquationExt_className[];
extern char g_igBlendEquationExt_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
int igBlendEquationExt_InitFields();

void igBlendEquationExt_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        1,                                            /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igBlendEquationExt_metaObject,     /* published MetaObject slot */
        igContextExt_Register,                        /* base class registrar */
        igContextExt_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igBlendEquationExt_GetMetaObject,       /* own MetaObject accessor (stored at +0x54) */
        igBlendEquationExt_className,      /* class name */
        0x18,                                         /* instance size */
        0,                                            /* vtable getter */
        &igBlendEquationExt_InitFields,               /* field adder */
        0,                                            /* extra callback item */
        0                                             /* callback list */
    );
}
