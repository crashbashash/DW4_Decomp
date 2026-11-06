/* 0x002b61e0 igUnsignedShortMetaField_Register: registers class igUnsignedShortMetaField with the object system, derived from igMetaField.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igMetaField_GetPublishedMetaObject[];
extern char igUnsignedShortMetaField_GetVTable[];
extern char thunk_igUnsignedShortMetaField_GetMetaObject[];
extern char igMetaField_Register[];
extern char g_igUnsignedShortMetaField_callbackList[];
extern char igUnsignedShortMetaField_className[];
extern char g_igUnsignedShortMetaField_metaObject[];
int igMetaObject_RegisterClass();

void igUnsignedShortMetaField_Register(void) {
    igMetaObject_RegisterClass(
        0,                                              /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igUnsignedShortMetaField_metaObject, /* published MetaObject slot */
        igMetaField_Register,                           /* base class registrar */
        igMetaField_GetPublishedMetaObject,    /* base class MetaObject accessor */
        thunk_igUnsignedShortMetaField_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igUnsignedShortMetaField_className,  /* class name */
        0x34,                                           /* instance size */
        igUnsignedShortMetaField_GetVTable,             /* vtable getter */
        0,                                              /* field adder */
        0,                                              /* extra callback item */
        g_igUnsignedShortMetaField_callbackList  /* callback list */
    );
}
