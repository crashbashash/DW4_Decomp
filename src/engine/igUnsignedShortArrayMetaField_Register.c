/* 0x002b64a0 igUnsignedShortArrayMetaField_Register: registers class igUnsignedShortArrayMetaField with the object system, derived from igUnsignedShortMetaField.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igUnsignedShortMetaField_Register[];
extern char igUnsignedShortArrayMetaField_GetVTable[];
extern char thunk_igUnsignedShortArrayMetaField_GetMetaObject[];
extern char igUnsignedShortMetaField_GetPublishedMetaObject[];
extern char g_igUnsignedShortArrayMetaField_callbackList[];
extern char igUnsignedShortArrayMetaField_className[];
extern char g_igUnsignedShortArrayMetaField_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igUnsignedShortArrayMetaField_InitFields();

void igUnsignedShortArrayMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                                        /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igUnsignedShortArrayMetaField_metaObject,      /* published MetaObject slot */
        igUnsignedShortMetaField_Register,                        /* base class registrar */
        igUnsignedShortMetaField_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igUnsignedShortArrayMetaField_GetMetaObject,        /* own MetaObject accessor (stored at +0x54) */
        igUnsignedShortArrayMetaField_className,       /* class name */
        0x38,                                                     /* instance size */
        igUnsignedShortArrayMetaField_GetVTable,                  /* vtable getter */
        &igUnsignedShortArrayMetaField_InitFields,                /* field adder */
        0,                                                        /* extra callback item */
        g_igUnsignedShortArrayMetaField_callbackList     /* callback list */
    );
}
