/* 0x0014f820 igDisableExt_Register: registers class igDisableExt with the object system, derived from igContextExt.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json.
 * The post-init hook is a three-instruction stub that stores thunk_igPsx2DisableExt_GetMetaObject
 * (the PS2 implementation) in this MetaObject's `_abstractProxy` (igMetaObject +0x3c). */
extern char igContextExt_GetPublishedMetaObject_0014bc40[];
extern char thunk_igDisableExt_GetMetaObject[];
extern char igContextExt_Register[];
extern char s_igDisableExt_className_004dcd58[];
extern char g_igDisableExt_metaObject_0055fea0[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
extern int igDisableExt_SetAbstractProxy_0014f8a0[4];
void igDisableExt_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        1,                                            /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igDisableExt_metaObject_0055fea0,           /* published MetaObject slot */
        igContextExt_Register,                        /* base class registrar */
        igContextExt_GetPublishedMetaObject_0014bc40, /* base class MetaObject accessor */
        thunk_igDisableExt_GetMetaObject,             /* own MetaObject accessor (stored at +0x54) */
        s_igDisableExt_className_004dcd58,            /* class name */
        0x14,                                         /* instance size */
        0,                                            /* vtable getter */
        &igDisableExt_SetAbstractProxy_0014f8a0[0],   /* post-init hook */
        0,                                            /* extra callback item */
        0                                             /* callback list */
    );
}
