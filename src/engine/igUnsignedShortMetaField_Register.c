/* 0x002b61e0 igUnsignedShortMetaField_Register: registers class igUnsignedShortMetaField with the object system, derived from igMetaField.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igMetaField_GetPublishedMetaObject_00187180[];
extern char igUnsignedShortMetaField_GetVTable[];
extern char thunk_igUnsignedShortMetaField_GetMetaObject[];
extern char igMetaField_Register[];
extern char g_igUnsignedShortMetaField_callbackList_004bf2a8[];
extern char s_igUnsignedShortMetaField_className_004f5ac0[];
extern char g_igUnsignedShortMetaField_metaObject_005856e8[];
int igMetaObject_RegisterClass();

void igUnsignedShortMetaField_Register(void) {
    igMetaObject_RegisterClass(
        0,                                              /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igUnsignedShortMetaField_metaObject_005856e8, /* published MetaObject slot */
        igMetaField_Register,                           /* base class registrar */
        igMetaField_GetPublishedMetaObject_00187180,    /* base class MetaObject accessor */
        thunk_igUnsignedShortMetaField_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igUnsignedShortMetaField_className_004f5ac0,  /* class name */
        0x34,                                           /* instance size */
        igUnsignedShortMetaField_GetVTable,             /* vtable getter */
        0,                                              /* field adder */
        0,                                              /* extra callback item */
        g_igUnsignedShortMetaField_callbackList_004bf2a8  /* callback list */
    );
}
