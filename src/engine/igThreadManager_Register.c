/* 0x002b7c10 igThreadManager_Register: registers class igThreadManager with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char thunk_igThreadManager_GetMetaObject[];
extern char igObject_Register[];
extern char g_igThreadManager_callbackList_004bf368[];
extern char s_igThreadManager_className_004f5be0[];
extern char g_igThreadManager_metaObject_00585790[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
extern int thunk_FUN_0030e480[4];
int igThreadManager_InitFields();

void igThreadManager_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        1,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igThreadManager_metaObject_00585790, /* published MetaObject slot */
        igObject_Register,                     /* base class registrar */
        igObject_GetMetaObject_ParentAccessor, /* base class MetaObject accessor */
        thunk_igThreadManager_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igThreadManager_className_004f5be0,  /* class name */
        0x10,                                  /* instance size */
        0,                                     /* vtable getter */
        &igThreadManager_InitFields,           /* field adder */
        thunk_FUN_0030e480,                    /* extra callback item */
        g_igThreadManager_callbackList_004bf368  /* callback list */
    );
}
