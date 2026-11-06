/* 0x0014daa0 igImageLoader_Register: registers class igImageLoader with the object system, derived from igImageUtils.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char thunk_igImageLoader_GetMetaObject[];
extern char igImageUtils_GetPublishedMetaObject[];
extern char igImageUtils_Register[];
extern char igImageLoader_className[];
extern char g_igImageLoader_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();

void igImageLoader_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        1,                                            /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igImageLoader_metaObject,          /* published MetaObject slot */
        igImageUtils_Register,                        /* base class registrar */
        igImageUtils_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igImageLoader_GetMetaObject,            /* own MetaObject accessor (stored at +0x54) */
        igImageLoader_className,           /* class name */
        8,                                            /* instance size */
        0,                                            /* vtable getter */
        0,                                            /* field adder */
        0,                                            /* extra callback item */
        0                                             /* callback list */
    );
}
