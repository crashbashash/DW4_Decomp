/* 0x002b64a0 igUnsignedShortArrayMetaField_Register: registers class igUnsignedShortArrayMetaField with the object system, derived from igUnsignedShortMetaField.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igUnsignedShortMetaField_Register[];
extern char igUnsignedShortArrayMetaField_GetVTable[];
extern char thunk_igUnsignedShortArrayMetaField_GetMetaObject[];
extern char igUnsignedShortMetaField_GetPublishedMetaObject_002b6530[];
extern char g_igUnsignedShortArrayMetaField_callbackList_004bf2b0[];
extern char s_igUnsignedShortArrayMetaField_className_004f5ae0[];
extern char g_igUnsignedShortArrayMetaField_metaObject_005856f8[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igUnsignedShortArrayMetaField_InitFields();

void igUnsignedShortArrayMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                                        /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igUnsignedShortArrayMetaField_metaObject_005856f8,      /* published MetaObject slot */
        igUnsignedShortMetaField_Register,                        /* base class registrar */
        igUnsignedShortMetaField_GetPublishedMetaObject_002b6530, /* base class MetaObject accessor */
        thunk_igUnsignedShortArrayMetaField_GetMetaObject,        /* own MetaObject accessor (stored at +0x54) */
        s_igUnsignedShortArrayMetaField_className_004f5ae0,       /* class name */
        0x38,                                                     /* instance size */
        igUnsignedShortArrayMetaField_GetVTable,                  /* vtable getter */
        &igUnsignedShortArrayMetaField_InitFields,                /* field adder */
        0,                                                        /* extra callback item */
        g_igUnsignedShortArrayMetaField_callbackList_004bf2b0     /* callback list */
    );
}
