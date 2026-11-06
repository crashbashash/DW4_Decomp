/* 0x002cc430 igCharArrayMetaField_Register: registers class igCharArrayMetaField with the object system, derived from igCharMetaField.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igCharMetaField_Register[];
extern char igCharArrayMetaField_GetVTable[];
extern char thunk_igCharArrayMetaField_GetMetaObject[];
extern char igCharMetaField_GetPublishedMetaObject[];
extern char g_igCharArrayMetaField_callbackList[];
extern char igCharArrayMetaField_className[];
extern char g_igCharArrayMetaField_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igCharArrayMetaField_InitFields();

void igCharArrayMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                               /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igCharArrayMetaField_metaObject,      /* published MetaObject slot */
        igCharMetaField_Register,                        /* base class registrar */
        igCharMetaField_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igCharArrayMetaField_GetMetaObject,        /* own MetaObject accessor (stored at +0x54) */
        igCharArrayMetaField_className,       /* class name */
        0x38,                                            /* instance size */
        igCharArrayMetaField_GetVTable,                  /* vtable getter */
        &igCharArrayMetaField_InitFields,                /* field adder */
        0,                                               /* extra callback item */
        g_igCharArrayMetaField_callbackList     /* callback list */
    );
}
