/* 0x00187690 igVec4fArrayMetaField_Register: registers class igVec4fArrayMetaField with the object system, derived from igVec4fMetaField.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVec4fMetaField_Register[];
extern char igVec4fArrayMetaField_GetVTable[];
extern char thunk_igVec4fArrayMetaField_GetMetaObject[];
extern char igVec4fMetaField_GetPublishedMetaObject[];
extern char g_igVec4fArrayMetaField_callbackList[];
extern char igVec4fArrayMetaField_className[];
extern char g_igVec4fArrayMetaField_metaObject[];
int FUN_00186a40();
int igMetaObject_RegisterClass();
int igVec4fArrayMetaField_InitFields();

void igVec4fArrayMetaField_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0,                                                /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igVec4fArrayMetaField_metaObject,      /* published MetaObject slot */
        igVec4fMetaField_Register,                        /* base class registrar */
        igVec4fMetaField_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igVec4fArrayMetaField_GetMetaObject,        /* own MetaObject accessor (stored at +0x54) */
        igVec4fArrayMetaField_className,       /* class name */
        0x38,                                             /* instance size */
        igVec4fArrayMetaField_GetVTable,                  /* vtable getter */
        &igVec4fArrayMetaField_InitFields,                /* field adder */
        0,                                                /* extra callback item */
        g_igVec4fArrayMetaField_callbackList     /* callback list */
    );
}
