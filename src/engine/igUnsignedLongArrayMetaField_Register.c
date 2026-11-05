/* 0x002b6b20 igUnsignedLongArrayMetaField_Register: registers class igUnsignedLongArrayMetaField with the object system, derived from igUnsignedLongMetaField.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igUnsignedLongMetaField_Register[];
extern char igUnsignedLongArrayMetaField_GetVTable[];
extern char thunk_igUnsignedLongArrayMetaField_GetMetaObject[];
extern char igUnsignedLongMetaField_GetPublishedMetaObject_002b6bb0[];
extern char g_igUnsignedLongArrayMetaField_callbackList_004bf2e0[];
extern char s_igUnsignedLongArrayMetaField_className_004f5b30[];
extern char g_igUnsignedLongArrayMetaField_metaObject_00585720[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igUnsignedLongArrayMetaField_InitFields();

void igUnsignedLongArrayMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                                       /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igUnsignedLongArrayMetaField_metaObject_00585720,      /* published MetaObject slot */
        igUnsignedLongMetaField_Register,                        /* base class registrar */
        igUnsignedLongMetaField_GetPublishedMetaObject_002b6bb0, /* base class MetaObject accessor */
        thunk_igUnsignedLongArrayMetaField_GetMetaObject,        /* own MetaObject accessor (stored at +0x54) */
        s_igUnsignedLongArrayMetaField_className_004f5b30,       /* class name */
        0x38,                                                    /* instance size */
        igUnsignedLongArrayMetaField_GetVTable,                  /* vtable getter */
        &igUnsignedLongArrayMetaField_InitFields,                /* field adder */
        0,                                                       /* extra callback item */
        g_igUnsignedLongArrayMetaField_callbackList_004bf2e0     /* callback list */
    );
}
