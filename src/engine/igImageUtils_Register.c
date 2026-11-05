/* 0x0014dcd0 igImageUtils_Register: registers class igImageUtils with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char thunk_igImageUtils_GetMetaObject[];
extern char igObject_Register[];
extern char s_igImageUtils_className_004dc860[];
extern char g_igImageUtils_metaObject_0055fd68[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();

void igImageUtils_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        1,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igImageUtils_metaObject_0055fd68,    /* published MetaObject slot */
        igObject_Register,                     /* base class registrar */
        igObject_GetMetaObject_ParentAccessor, /* base class MetaObject accessor */
        thunk_igImageUtils_GetMetaObject,      /* own MetaObject accessor (stored at +0x54) */
        s_igImageUtils_className_004dc860,     /* class name */
        8,                                     /* instance size */
        0,                                     /* vtable getter */
        0,                                     /* field adder */
        0,                                     /* extra callback item */
        0                                      /* callback list */
    );
}
