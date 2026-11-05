/* 0x0014daa0 igImageLoader_Register: registers class igImageLoader with the object system, derived from igImageUtils.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char thunk_igImageLoader_GetMetaObject[];
extern char igImageUtils_GetPublishedMetaObject_0014db10[];
extern char igImageUtils_Register[];
extern char s_igImageLoader_className_004dc840[];
extern char g_igImageLoader_metaObject_0055fd58[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();

void igImageLoader_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        1,                                            /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igImageLoader_metaObject_0055fd58,          /* published MetaObject slot */
        igImageUtils_Register,                        /* base class registrar */
        igImageUtils_GetPublishedMetaObject_0014db10, /* base class MetaObject accessor */
        thunk_igImageLoader_GetMetaObject,            /* own MetaObject accessor (stored at +0x54) */
        s_igImageLoader_className_004dc840,           /* class name */
        8,                                            /* instance size */
        0,                                            /* vtable getter */
        0,                                            /* field adder */
        0,                                            /* extra callback item */
        0                                             /* callback list */
    );
}
