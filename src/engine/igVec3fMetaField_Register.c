/* 0x001879c0 igVec3fMetaField_Register: registers class igVec3fMetaField with the object system, derived from igMetaField.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igMetaField_GetPublishedMetaObject_00187180[];
extern char igVec3fMetaField_GetVTable[];
extern char thunk_igVec3fMetaField_GetMetaObject[];
extern char igMetaField_Register[];
extern char g_igVec3fMetaField_callbackList_0048ad90[];
extern char s_igVec3fMetaField_className_004e0a40[];
extern char g_igVec3fMetaField_metaObject_00560f70[];
int FUN_00186a40();
int igMetaObject_RegisterClass();

void igVec3fMetaField_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0,                                           /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igVec3fMetaField_metaObject_00560f70,      /* published MetaObject slot */
        igMetaField_Register,                        /* base class registrar */
        igMetaField_GetPublishedMetaObject_00187180, /* base class MetaObject accessor */
        thunk_igVec3fMetaField_GetMetaObject,        /* own MetaObject accessor (stored at +0x54) */
        s_igVec3fMetaField_className_004e0a40,       /* class name */
        0x34,                                        /* instance size */
        igVec3fMetaField_GetVTable,                  /* vtable getter */
        0,                                           /* field adder */
        0,                                           /* extra callback item */
        g_igVec3fMetaField_callbackList_0048ad90     /* callback list */
    );
}
