/* 0x002cb990 igContextExt_Register: registers class igContextExt with the object system, derived from igContext.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igContext_GetPublishedMetaObject_0014a170[];
extern char thunk_igContextExt_GetMetaObject[];
extern char igContext_Register[];
extern char s_igContextExt_className_004f86f8[];
extern char g_igContextExt_metaObject_005868e8[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igContextExt_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        1,                                         /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igContextExt_metaObject_005868e8,        /* published MetaObject slot */
        igContext_Register,                        /* base class registrar */
        igContext_GetPublishedMetaObject_0014a170, /* base class MetaObject accessor */
        thunk_igContextExt_GetMetaObject,          /* own MetaObject accessor (stored at +0x54) */
        s_igContextExt_className_004f86f8,         /* class name */
        0x14,                                      /* instance size */
        0,                                         /* vtable getter */
        0,                                         /* field adder */
        0,                                         /* extra callback item */
        0                                          /* callback list */
    );
}
