/* 0x002b7510 igUnsignedCharMetaField_Register: registers class igUnsignedCharMetaField with the object system, derived from igMetaField.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igMetaField_GetPublishedMetaObject[];
extern char igUnsignedCharMetaField_GetVTable[];
extern char thunk_igUnsignedCharMetaField_GetMetaObject[];
extern char igMetaField_Register[];
extern char g_igUnsignedCharMetaField_callbackList[];
extern char igUnsignedCharMetaField_className[];
extern char g_igUnsignedCharMetaField_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igUnsignedCharMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                             /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igUnsignedCharMetaField_metaObject, /* published MetaObject slot */
        igMetaField_Register,                          /* base class registrar */
        igMetaField_GetPublishedMetaObject,   /* base class MetaObject accessor */
        thunk_igUnsignedCharMetaField_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igUnsignedCharMetaField_className,  /* class name */
        0x34,                                          /* instance size */
        igUnsignedCharMetaField_GetVTable,             /* vtable getter */
        0,                                             /* field adder */
        0,                                             /* extra callback item */
        g_igUnsignedCharMetaField_callbackList  /* callback list */
    );
}
