/* 0x002cbd50 igCompoundMetaField_Register: registers class igCompoundMetaField with the object system, derived from igMetaField.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igMetaField_GetPublishedMetaObject[];
extern char igMetaField_Register[];
extern char thunk_igCompoundMetaField_GetMetaObject[];
extern char g_igCompoundMetaField_callbackList[];
extern char igCompoundMetaField_className[];
extern char g_igCompoundMetaField_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igCompoundMetaField_InitFields();

void igCompoundMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        1,                                           /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igCompoundMetaField_metaObject,   /* published MetaObject slot */
        igMetaField_Register,                        /* base class registrar */
        igMetaField_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igCompoundMetaField_GetMetaObject,     /* own MetaObject accessor (stored at +0x54) */
        igCompoundMetaField_className,    /* class name */
        0x38,                                        /* instance size */
        0,                                           /* vtable getter */
        &igCompoundMetaField_InitFields,             /* field adder */
        0,                                           /* extra callback item */
        g_igCompoundMetaField_callbackList  /* callback list */
    );
}
