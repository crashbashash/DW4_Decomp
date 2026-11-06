/* 0x002c3200 igIntArrayMetaField_Register: registers class igIntArrayMetaField with the object system, derived from igIntMetaField.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igIntMetaField_Register[];
extern char igIntArrayMetaField_GetVTable[];
extern char thunk_igIntArrayMetaField_GetMetaObject[];
extern char igIntMetaField_GetPublishedMetaObject[];
extern char g_igIntArrayMetaField_callbackList[];
extern char igIntArrayMetaField_className[];
extern char g_igIntArrayMetaField_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igIntArrayMetaField_InitFields();

void igIntArrayMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                              /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igIntArrayMetaField_metaObject,      /* published MetaObject slot */
        igIntMetaField_Register,                        /* base class registrar */
        igIntMetaField_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igIntArrayMetaField_GetMetaObject,        /* own MetaObject accessor (stored at +0x54) */
        igIntArrayMetaField_className,       /* class name */
        0x38,                                           /* instance size */
        igIntArrayMetaField_GetVTable,                  /* vtable getter */
        &igIntArrayMetaField_InitFields,                /* field adder */
        0,                                              /* extra callback item */
        g_igIntArrayMetaField_callbackList     /* callback list */
    );
}
