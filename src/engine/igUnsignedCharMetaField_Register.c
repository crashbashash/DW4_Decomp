/* 0x002b7510 igUnsignedCharMetaField_Register: registers class igUnsignedCharMetaField with the object system, derived from igMetaField.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igMetaField_GetPublishedMetaObject_00187180[];
extern char igUnsignedCharMetaField_GetVTable[];
extern char thunk_igUnsignedCharMetaField_GetMetaObject[];
extern char igMetaField_Register[];
extern char g_igUnsignedCharMetaField_callbackList_004bf338[];
extern char s_igUnsignedCharMetaField_className_004f5b90[];
extern char g_igUnsignedCharMetaField_metaObject_00585760[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igUnsignedCharMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                             /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igUnsignedCharMetaField_metaObject_00585760, /* published MetaObject slot */
        igMetaField_Register,                          /* base class registrar */
        igMetaField_GetPublishedMetaObject_00187180,   /* base class MetaObject accessor */
        thunk_igUnsignedCharMetaField_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igUnsignedCharMetaField_className_004f5b90,  /* class name */
        0x34,                                          /* instance size */
        igUnsignedCharMetaField_GetVTable,             /* vtable getter */
        0,                                             /* field adder */
        0,                                             /* extra callback item */
        g_igUnsignedCharMetaField_callbackList_004bf338  /* callback list */
    );
}
