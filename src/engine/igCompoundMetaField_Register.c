/* 0x002cbd50 igCompoundMetaField_Register: registers class igCompoundMetaField with the object system, derived from igMetaField.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igMetaField_GetPublishedMetaObject_00187180[];
extern char igMetaField_Register[];
extern char thunk_igCompoundMetaField_GetMetaObject[];
extern char g_igCompoundMetaField_callbackList_004c14b8[];
extern char s_igCompoundMetaField_className_004f8760[];
extern char g_igCompoundMetaField_metaObject_00586918[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igCompoundMetaField_InitFields();

void igCompoundMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        1,                                           /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igCompoundMetaField_metaObject_00586918,   /* published MetaObject slot */
        igMetaField_Register,                        /* base class registrar */
        igMetaField_GetPublishedMetaObject_00187180, /* base class MetaObject accessor */
        thunk_igCompoundMetaField_GetMetaObject,     /* own MetaObject accessor (stored at +0x54) */
        s_igCompoundMetaField_className_004f8760,    /* class name */
        0x38,                                        /* instance size */
        0,                                           /* vtable getter */
        &igCompoundMetaField_InitFields,             /* field adder */
        0,                                           /* extra callback item */
        g_igCompoundMetaField_callbackList_004c14b8  /* callback list */
    );
}
