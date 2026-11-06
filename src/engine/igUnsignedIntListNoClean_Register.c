/* 0x002ca390 igUnsignedIntListNoClean_Register: registers class igUnsignedIntListNoClean with the object system, derived from igUnsignedIntList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igUnsignedIntList_GetPublishedMetaObject[];
extern char igUnsignedIntListNoClean_GetVTable[];
extern char thunk_igUnsignedIntListNoClean_GetMetaObject[];
extern char igUnsignedIntList_Register[];
extern char igUnsignedIntListNoClean_className[];
extern char g_igUnsignedIntListNoClean_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igUnsignedIntListNoClean_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igUnsignedIntListNoClean_metaObject,    /* published MetaObject slot */
        igUnsignedIntList_Register,                        /* base class registrar */
        igUnsignedIntList_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igUnsignedIntListNoClean_GetMetaObject,      /* own MetaObject accessor (stored at +0x54) */
        igUnsignedIntListNoClean_className,     /* class name */
        0x14,                                              /* instance size */
        igUnsignedIntListNoClean_GetVTable,                /* vtable getter */
        0,                                                 /* field adder */
        0,                                                 /* extra callback item */
        0                                                  /* callback list */
    );
}
