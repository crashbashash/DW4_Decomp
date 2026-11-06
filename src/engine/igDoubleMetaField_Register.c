/* 0x002c6cd0 igDoubleMetaField_Register: registers class igDoubleMetaField with the object system, derived from igMetaField.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igMetaField_GetPublishedMetaObject[];
extern char igMetaField_Register[];
extern char igDoubleMetaField_GetVTable[];
extern char thunk_igDoubleMetaField_GetMetaObject[];
extern char g_igDoubleMetaField_callbackList[];
extern char igDoubleMetaField_className[];
extern char g_igDoubleMetaField_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igDoubleMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                           /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igDoubleMetaField_metaObject,     /* published MetaObject slot */
        igMetaField_Register,                        /* base class registrar */
        igMetaField_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igDoubleMetaField_GetMetaObject,       /* own MetaObject accessor (stored at +0x54) */
        igDoubleMetaField_className,      /* class name */
        0x34,                                        /* instance size */
        igDoubleMetaField_GetVTable,                 /* vtable getter */
        0,                                           /* field adder */
        0,                                           /* extra callback item */
        g_igDoubleMetaField_callbackList    /* callback list */
    );
}
