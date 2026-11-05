/* 0x002bc1c0 igQueue_Register: registers class igQueue with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char thunk_igQueue_GetMetaObject[];
extern char igObject_Register[];
extern char g_igQueue_callbackList_004bf9b0[];
extern char s_igQueue_className_004f62c8[];
extern char g_igQueue_metaObject_00585aa8[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igQueue_InitFields();

void igQueue_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        1,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igQueue_metaObject_00585aa8,         /* published MetaObject slot */
        igObject_Register,                     /* base class registrar */
        igObject_GetMetaObject_ParentAccessor, /* base class MetaObject accessor */
        thunk_igQueue_GetMetaObject,           /* own MetaObject accessor (stored at +0x54) */
        s_igQueue_className_004f62c8,          /* class name */
        0xC,                                   /* instance size */
        0,                                     /* vtable getter */
        &igQueue_InitFields,                   /* field adder */
        0,                                     /* extra callback item */
        g_igQueue_callbackList_004bf9b0        /* callback list */
    );
}
