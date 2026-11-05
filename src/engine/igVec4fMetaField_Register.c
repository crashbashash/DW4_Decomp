/* 0x001873d0 igVec4fMetaField_Register: registers class igVec4fMetaField with the object system, derived from igMetaField.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igMetaField_GetPublishedMetaObject_00187180[];
extern char igVec4fMetaField_GetVTable[];
extern char thunk_igVec4fMetaField_GetMetaObject[];
extern char igMetaField_Register[];
extern char g_igVec4fMetaField_callbackList_0048ad60[];
extern char s_igVec4fMetaField_className_004e0a00[];
extern char g_igVec4fMetaField_metaObject_00560f38[];
int FUN_00186a40();
int igMetaObject_RegisterClass();

void igVec4fMetaField_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0,                                           /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igVec4fMetaField_metaObject_00560f38,      /* published MetaObject slot */
        igMetaField_Register,                        /* base class registrar */
        igMetaField_GetPublishedMetaObject_00187180, /* base class MetaObject accessor */
        thunk_igVec4fMetaField_GetMetaObject,        /* own MetaObject accessor (stored at +0x54) */
        s_igVec4fMetaField_className_004e0a00,       /* class name */
        0x34,                                        /* instance size */
        igVec4fMetaField_GetVTable,                  /* vtable getter */
        0,                                           /* field adder */
        0,                                           /* extra callback item */
        g_igVec4fMetaField_callbackList_0048ad60     /* callback list */
    );
}
