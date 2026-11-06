/* 0x002ca9e0 igIntListNoClean_Register: registers class igIntListNoClean with the object system, derived from igIntList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igIntListNoClean_GetVTable[];
extern char thunk_igIntListNoClean_GetMetaObject[];
extern char igIntList_GetPublishedMetaObject[];
extern char igIntList_Register[];
extern char igIntListNoClean_className[];
extern char g_igIntListNoClean_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igIntListNoClean_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                         /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igIntListNoClean_metaObject,    /* published MetaObject slot */
        igIntList_Register,                        /* base class registrar */
        igIntList_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igIntListNoClean_GetMetaObject,      /* own MetaObject accessor (stored at +0x54) */
        igIntListNoClean_className,     /* class name */
        0x14,                                      /* instance size */
        igIntListNoClean_GetVTable,                /* vtable getter */
        0,                                         /* field adder */
        0,                                         /* extra callback item */
        0                                          /* callback list */
    );
}
