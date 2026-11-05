/* 0x0014dbc0 igImageConvert_Register: registers class igImageConvert with the object system, derived from igImageUtils.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json.
 * The post-init hook is a three-instruction stub that stores thunk_igPsx2ImageConvert_GetMetaObject
 * (the PS2 implementation) in this MetaObject's `_abstractProxy` (igMetaObject +0x3c). */
extern char igImageUtils_GetPublishedMetaObject_0014db10[];
extern char thunk_igImageConvert_GetMetaObject[];
extern char igImageUtils_Register[];
extern char s_igImageConvert_className_004dc850[];
extern char g_igImageConvert_metaObject_0055fd60[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
extern int igImageConvert_SetAbstractProxy_0014dc40[4];
void igImageConvert_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        1,                                            /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igImageConvert_metaObject_0055fd60,         /* published MetaObject slot */
        igImageUtils_Register,                        /* base class registrar */
        igImageUtils_GetPublishedMetaObject_0014db10, /* base class MetaObject accessor */
        thunk_igImageConvert_GetMetaObject,           /* own MetaObject accessor (stored at +0x54) */
        s_igImageConvert_className_004dc850,          /* class name */
        8,                                            /* instance size */
        0,                                            /* vtable getter */
        &igImageConvert_SetAbstractProxy_0014dc40[0], /* post-init hook */
        0,                                            /* extra callback item */
        0                                             /* callback list */
    );
}
