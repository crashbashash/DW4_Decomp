/* 0x00187100 igVec4ucMetaField_Register: registers class igVec4ucMetaField with the object system, derived from igMetaField.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVec4ucMetaField_GetVTable[];
extern char thunk_igVec4ucMetaField_GetMetaObject_00187170[];
extern char igMetaField_GetPublishedMetaObject[];
extern char igMetaField_Register[];
extern char g_igVec4ucMetaField_callbackList[];
extern char igVec4ucMetaField_className[];
extern char g_igVec4ucMetaField_metaObject[];
int FUN_00186a40();
int igMetaObject_RegisterClass();

void igVec4ucMetaField_Register(void) {
    FUN_00186a40();  /* one-shot static-init guard (byte flag), chaining to sibling init stubs */
    igMetaObject_RegisterClass(
        0,                                           /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igVec4ucMetaField_metaObject,     /* published MetaObject slot */
        igMetaField_Register,                        /* base class registrar */
        igMetaField_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igVec4ucMetaField_GetMetaObject_00187170,                                /* own MetaObject accessor (stored at +0x54) */
        igVec4ucMetaField_className,      /* class name */
        0x34,                                        /* instance size */
        igVec4ucMetaField_GetVTable,                 /* vtable getter */
        0,                                           /* field adder */
        0,                                           /* extra callback item */
        g_igVec4ucMetaField_callbackList    /* callback list */
    );
}
