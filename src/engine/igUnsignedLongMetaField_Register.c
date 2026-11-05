/* 0x002b68a0 igUnsignedLongMetaField_Register: registers class igUnsignedLongMetaField with the object system, derived from igMetaField.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igMetaField_GetPublishedMetaObject_00187180[];
extern char igUnsignedLongMetaField_GetVTable[];
extern char thunk_igUnsignedLongMetaField_GetMetaObject[];
extern char igMetaField_Register[];
extern char g_igUnsignedLongMetaField_callbackList_004bf2d8[];
extern char s_igUnsignedLongMetaField_className_004f5b10[];
extern char g_igUnsignedLongMetaField_metaObject_00585710[];
int igMetaObject_RegisterClass();

void igUnsignedLongMetaField_Register(void) {
    igMetaObject_RegisterClass(
        0,                                             /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igUnsignedLongMetaField_metaObject_00585710, /* published MetaObject slot */
        igMetaField_Register,                          /* base class registrar */
        igMetaField_GetPublishedMetaObject_00187180,   /* base class MetaObject accessor */
        thunk_igUnsignedLongMetaField_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igUnsignedLongMetaField_className_004f5b10,  /* class name */
        0x34,                                          /* instance size */
        igUnsignedLongMetaField_GetVTable,             /* vtable getter */
        0,                                             /* field adder */
        0,                                             /* extra callback item */
        g_igUnsignedLongMetaField_callbackList_004bf2d8  /* callback list */
    );
}
