/* 0x002bed50 igMetaField_Register: registers class igMetaField with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char thunk_igMetaField_GetMetaObject[];
extern char igObject_Register[];
extern char g_igMetaField_callbackList_004bfdf0[];
extern char s_igMetaField_className_004f67a0[];
extern char g_igMetaField_metaObject_00585cc8[];
int igMetaObject_RegisterClass();
int igMetaField_InitFields();

void igMetaField_Register(void) {
    igMetaObject_RegisterClass(
        1,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igMetaField_metaObject_00585cc8,     /* published MetaObject slot */
        igObject_Register,                     /* base class registrar */
        igObject_GetMetaObject_ParentAccessor, /* base class MetaObject accessor */
        thunk_igMetaField_GetMetaObject,       /* own MetaObject accessor (stored at +0x54) */
        s_igMetaField_className_004f67a0,      /* class name */
        0x34,                                  /* instance size */
        0,                                     /* vtable getter */
        &igMetaField_InitFields,               /* field adder */
        0,                                     /* extra callback item */
        g_igMetaField_callbackList_004bfdf0    /* callback list */
    );
}
