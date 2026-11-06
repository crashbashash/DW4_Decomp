/* 0x002b9d90 igStringArrayMetaField_Register: registers class igStringArrayMetaField with the object system, derived from igStringMetaField.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igStringMetaField_Register[];
extern char igStringArrayMetaField_GetVTable[];
extern char thunk_igStringArrayMetaField_GetMetaObject[];
extern char igStringMetaField_GetPublishedMetaObject[];
extern char g_igStringArrayMetaField_callbackList[];
extern char igStringArrayMetaField_className[];
extern char g_igStringArrayMetaField_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igStringArrayMetaField_InitFields();

void igStringArrayMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igStringArrayMetaField_metaObject,      /* published MetaObject slot */
        igStringMetaField_Register,                        /* base class registrar */
        igStringMetaField_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igStringArrayMetaField_GetMetaObject,        /* own MetaObject accessor (stored at +0x54) */
        igStringArrayMetaField_className,       /* class name */
        0x40,                                              /* instance size */
        igStringArrayMetaField_GetVTable,                  /* vtable getter */
        &igStringArrayMetaField_InitFields,                /* field adder */
        0,                                                 /* extra callback item */
        g_igStringArrayMetaField_callbackList     /* callback list */
    );
}
