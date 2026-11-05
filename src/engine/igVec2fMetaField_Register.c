/* 0x00187c80 igVec2fMetaField_Register: registers class igVec2fMetaField with the object system, derived from igMetaField.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igMetaField_GetPublishedMetaObject_00187180[];
extern char igVec2fMetaField_GetVTable[];
extern char thunk_igVec2fMetaField_GetMetaObject[];
extern char igMetaField_Register[];
extern char g_igVec2fMetaField_callbackList_0048ad98[];
extern char s_igVec2fMetaField_className_004e0a60[];
extern char g_igVec2fMetaField_metaObject_00560f88[];
int FUN_00186a40();
int igMetaObject_RegisterClass();

void igVec2fMetaField_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0,                                           /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igVec2fMetaField_metaObject_00560f88,      /* published MetaObject slot */
        igMetaField_Register,                        /* base class registrar */
        igMetaField_GetPublishedMetaObject_00187180, /* base class MetaObject accessor */
        thunk_igVec2fMetaField_GetMetaObject,        /* own MetaObject accessor (stored at +0x54) */
        s_igVec2fMetaField_className_004e0a60,       /* class name */
        0x34,                                        /* instance size */
        igVec2fMetaField_GetVTable,                  /* vtable getter */
        0,                                           /* field adder */
        0,                                           /* extra callback item */
        g_igVec2fMetaField_callbackList_0048ad98     /* callback list */
    );
}
