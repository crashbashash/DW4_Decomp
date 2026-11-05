/* 0x00187100 igVec4ucMetaField_Register: registers class igVec4ucMetaField with the object system, derived from igMetaField.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVec4ucMetaField_GetVTable[];
extern char thunk_igVec4ucMetaField_GetMetaObject_00187170[];
extern char igMetaField_GetPublishedMetaObject_00187180[];
extern char igMetaField_Register[];
extern char g_igVec4ucMetaField_callbackList_0048ad58[];
extern char s_igVec4ucMetaField_className_004e09e0[];
extern char g_igVec4ucMetaField_metaObject_00560f28[];
int FUN_00186a40();
int igMetaObject_RegisterClass();

void igVec4ucMetaField_Register(void) {
    FUN_00186a40();  /* one-shot static-init guard (byte flag), chaining to sibling init stubs */
    igMetaObject_RegisterClass(
        0,                                           /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igVec4ucMetaField_metaObject_00560f28,     /* published MetaObject slot */
        igMetaField_Register,                        /* base class registrar */
        igMetaField_GetPublishedMetaObject_00187180, /* base class MetaObject accessor */
        thunk_igVec4ucMetaField_GetMetaObject_00187170,                                /* own MetaObject accessor (stored at +0x54) */
        s_igVec4ucMetaField_className_004e09e0,      /* class name */
        0x34,                                        /* instance size */
        igVec4ucMetaField_GetVTable,                 /* vtable getter */
        0,                                           /* field adder */
        0,                                           /* extra callback item */
        g_igVec4ucMetaField_callbackList_0048ad58    /* callback list */
    );
}
