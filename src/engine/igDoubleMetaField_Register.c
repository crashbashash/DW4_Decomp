/* 0x002c6cd0 igDoubleMetaField_Register: registers class igDoubleMetaField with the object system, derived from igMetaField.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igMetaField_GetPublishedMetaObject_00187180[];
extern char igMetaField_Register[];
extern char igDoubleMetaField_GetVTable[];
extern char thunk_igDoubleMetaField_GetMetaObject[];
extern char g_igDoubleMetaField_callbackList_004c10b8[];
extern char s_igDoubleMetaField_className_004f8100[];
extern char g_igDoubleMetaField_metaObject_00586638[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igDoubleMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                           /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igDoubleMetaField_metaObject_00586638,     /* published MetaObject slot */
        igMetaField_Register,                        /* base class registrar */
        igMetaField_GetPublishedMetaObject_00187180, /* base class MetaObject accessor */
        thunk_igDoubleMetaField_GetMetaObject,       /* own MetaObject accessor (stored at +0x54) */
        s_igDoubleMetaField_className_004f8100,      /* class name */
        0x34,                                        /* instance size */
        igDoubleMetaField_GetVTable,                 /* vtable getter */
        0,                                           /* field adder */
        0,                                           /* extra callback item */
        g_igDoubleMetaField_callbackList_004c10b8    /* callback list */
    );
}
