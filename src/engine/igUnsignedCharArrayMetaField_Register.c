/* 0x002b77d0 igUnsignedCharArrayMetaField_Register: registers class igUnsignedCharArrayMetaField with the object system, derived from igUnsignedCharMetaField.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igUnsignedCharMetaField_Register[];
extern char igUnsignedCharArrayMetaField_GetVTable[];
extern char thunk_igUnsignedCharArrayMetaField_GetMetaObject[];
extern char igUnsignedCharMetaField_GetPublishedMetaObject[];
extern char g_igUnsignedCharArrayMetaField_callbackList[];
extern char igUnsignedCharArrayMetaField_className[];
extern char g_igUnsignedCharArrayMetaField_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igUnsignedCharArrayMetaField_InitFields();

void igUnsignedCharArrayMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                                       /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igUnsignedCharArrayMetaField_metaObject,      /* published MetaObject slot */
        igUnsignedCharMetaField_Register,                        /* base class registrar */
        igUnsignedCharMetaField_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igUnsignedCharArrayMetaField_GetMetaObject,        /* own MetaObject accessor (stored at +0x54) */
        igUnsignedCharArrayMetaField_className,       /* class name */
        0x38,                                                    /* instance size */
        igUnsignedCharArrayMetaField_GetVTable,                  /* vtable getter */
        &igUnsignedCharArrayMetaField_InitFields,                /* field adder */
        0,                                                       /* extra callback item */
        g_igUnsignedCharArrayMetaField_callbackList     /* callback list */
    );
}
