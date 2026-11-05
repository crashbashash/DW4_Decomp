/* 0x002b71e0 igUnsignedIntArrayMetaField_Register: registers class igUnsignedIntArrayMetaField with the object system, derived from igUnsignedIntMetaField.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igUnsignedIntMetaField_Register[];
extern char igUnsignedIntArrayMetaField_GetVTable[];
extern char thunk_igUnsignedIntArrayMetaField_GetMetaObject[];
extern char igUnsignedIntMetaField_GetPublishedMetaObject_002b7270[];
extern char g_igUnsignedIntArrayMetaField_callbackList_004bf310[];
extern char s_igUnsignedIntArrayMetaField_className_004f5b70[];
extern char g_igUnsignedIntArrayMetaField_metaObject_00585748[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igUnsignedIntArrayMetaField_InitFields();

void igUnsignedIntArrayMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                                      /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igUnsignedIntArrayMetaField_metaObject_00585748,      /* published MetaObject slot */
        igUnsignedIntMetaField_Register,                        /* base class registrar */
        igUnsignedIntMetaField_GetPublishedMetaObject_002b7270, /* base class MetaObject accessor */
        thunk_igUnsignedIntArrayMetaField_GetMetaObject,        /* own MetaObject accessor (stored at +0x54) */
        s_igUnsignedIntArrayMetaField_className_004f5b70,       /* class name */
        0x38,                                                   /* instance size */
        igUnsignedIntArrayMetaField_GetVTable,                  /* vtable getter */
        &igUnsignedIntArrayMetaField_InitFields,                /* field adder */
        0,                                                      /* extra callback item */
        g_igUnsignedIntArrayMetaField_callbackList_004bf310     /* callback list */
    );
}
