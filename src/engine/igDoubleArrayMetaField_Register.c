/* 0x002c6f50 igDoubleArrayMetaField_Register: registers class igDoubleArrayMetaField with the object system, derived from igDoubleMetaField.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igDoubleMetaField_Register[];
extern char igDoubleArrayMetaField_GetVTable[];
extern char thunk_igDoubleArrayMetaField_GetMetaObject[];
extern char igDoubleMetaField_GetPublishedMetaObject[];
extern char g_igDoubleArrayMetaField_callbackList[];
extern char igDoubleArrayMetaField_className[];
extern char g_igDoubleArrayMetaField_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igDoubleArrayMetaField_InitFields();

void igDoubleArrayMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igDoubleArrayMetaField_metaObject,      /* published MetaObject slot */
        igDoubleMetaField_Register,                        /* base class registrar */
        igDoubleMetaField_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igDoubleArrayMetaField_GetMetaObject,        /* own MetaObject accessor (stored at +0x54) */
        igDoubleArrayMetaField_className,       /* class name */
        0x38,                                              /* instance size */
        igDoubleArrayMetaField_GetVTable,                  /* vtable getter */
        &igDoubleArrayMetaField_InitFields,                /* field adder */
        0,                                                 /* extra callback item */
        g_igDoubleArrayMetaField_callbackList     /* callback list */
    );
}
