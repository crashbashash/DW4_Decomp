/* 0x001879c0 igVec3fMetaField_Register: registers class igVec3fMetaField with the object system, derived from igMetaField.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igMetaField_GetPublishedMetaObject[];
extern char igVec3fMetaField_GetVTable[];
extern char thunk_igVec3fMetaField_GetMetaObject[];
extern char igMetaField_Register[];
extern char g_igVec3fMetaField_callbackList[];
extern char igVec3fMetaField_className[];
extern char g_igVec3fMetaField_metaObject[];
int FUN_00186a40();
int igMetaObject_RegisterClass();

void igVec3fMetaField_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0,                                           /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igVec3fMetaField_metaObject,      /* published MetaObject slot */
        igMetaField_Register,                        /* base class registrar */
        igMetaField_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igVec3fMetaField_GetMetaObject,        /* own MetaObject accessor (stored at +0x54) */
        igVec3fMetaField_className,       /* class name */
        0x34,                                        /* instance size */
        igVec3fMetaField_GetVTable,                  /* vtable getter */
        0,                                           /* field adder */
        0,                                           /* extra callback item */
        g_igVec3fMetaField_callbackList     /* callback list */
    );
}
