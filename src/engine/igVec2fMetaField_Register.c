/* 0x00187c80 igVec2fMetaField_Register: registers class igVec2fMetaField with the object system, derived from igMetaField.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igMetaField_GetPublishedMetaObject[];
extern char igVec2fMetaField_GetVTable[];
extern char thunk_igVec2fMetaField_GetMetaObject[];
extern char igMetaField_Register[];
extern char g_igVec2fMetaField_callbackList[];
extern char igVec2fMetaField_className[];
extern char g_igVec2fMetaField_metaObject[];
int FUN_00186a40();
int igMetaObject_RegisterClass();

void igVec2fMetaField_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0,                                           /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igVec2fMetaField_metaObject,      /* published MetaObject slot */
        igMetaField_Register,                        /* base class registrar */
        igMetaField_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igVec2fMetaField_GetMetaObject,        /* own MetaObject accessor (stored at +0x54) */
        igVec2fMetaField_className,       /* class name */
        0x34,                                        /* instance size */
        igVec2fMetaField_GetVTable,                  /* vtable getter */
        0,                                           /* field adder */
        0,                                           /* extra callback item */
        g_igVec2fMetaField_callbackList     /* callback list */
    );
}
