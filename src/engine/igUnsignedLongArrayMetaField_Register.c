/* 0x002b6b20 igUnsignedLongArrayMetaField_Register: registers class igUnsignedLongArrayMetaField with the object system, derived from igUnsignedLongMetaField.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igUnsignedLongMetaField_Register[];
extern char igUnsignedLongArrayMetaField_GetVTable[];
extern char thunk_igUnsignedLongArrayMetaField_GetMetaObject[];
extern char igUnsignedLongMetaField_GetPublishedMetaObject[];
extern char g_igUnsignedLongArrayMetaField_callbackList[];
extern char igUnsignedLongArrayMetaField_className[];
extern char g_igUnsignedLongArrayMetaField_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igUnsignedLongArrayMetaField_InitFields();

void igUnsignedLongArrayMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                                       /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igUnsignedLongArrayMetaField_metaObject,      /* published MetaObject slot */
        igUnsignedLongMetaField_Register,                        /* base class registrar */
        igUnsignedLongMetaField_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igUnsignedLongArrayMetaField_GetMetaObject,        /* own MetaObject accessor (stored at +0x54) */
        igUnsignedLongArrayMetaField_className,       /* class name */
        0x38,                                                    /* instance size */
        igUnsignedLongArrayMetaField_GetVTable,                  /* vtable getter */
        &igUnsignedLongArrayMetaField_InitFields,                /* field adder */
        0,                                                       /* extra callback item */
        g_igUnsignedLongArrayMetaField_callbackList     /* callback list */
    );
}
