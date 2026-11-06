/* 0x002cadd0 igCharListNoClean_Register: registers class igCharListNoClean with the object system, derived from igCharList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igCharListNoClean_GetVTable[];
extern char thunk_igCharListNoClean_GetMetaObject[];
extern char igCharList_GetPublishedMetaObject[];
extern char igCharList_Register[];
extern char igCharListNoClean_className[];
extern char g_igCharListNoClean_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igCharListNoClean_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                          /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igCharListNoClean_metaObject,    /* published MetaObject slot */
        igCharList_Register,                        /* base class registrar */
        igCharList_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igCharListNoClean_GetMetaObject,      /* own MetaObject accessor (stored at +0x54) */
        igCharListNoClean_className,     /* class name */
        0x14,                                       /* instance size */
        igCharListNoClean_GetVTable,                /* vtable getter */
        0,                                          /* field adder */
        0,                                          /* extra callback item */
        0                                           /* callback list */
    );
}
