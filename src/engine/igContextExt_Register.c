/* 0x002cb990 igContextExt_Register: registers class igContextExt with the object system, derived from igContext.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igContext_GetPublishedMetaObject[];
extern char thunk_igContextExt_GetMetaObject[];
extern char igContext_Register[];
extern char igContextExt_className[];
extern char g_igContextExt_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igContextExt_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        1,                                         /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igContextExt_metaObject,        /* published MetaObject slot */
        igContext_Register,                        /* base class registrar */
        igContext_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igContextExt_GetMetaObject,          /* own MetaObject accessor (stored at +0x54) */
        igContextExt_className,         /* class name */
        0x14,                                      /* instance size */
        0,                                         /* vtable getter */
        0,                                         /* field adder */
        0,                                         /* extra callback item */
        0                                          /* callback list */
    );
}
