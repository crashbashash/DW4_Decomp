/* 0x002b8fa0 igStringTable_Register: registers class igStringTable with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igStringTable_GetVTable[];
extern char thunk_igStringTable_GetMetaObject[];
extern char igObject_Register[];
extern char g_igStringTable_callbackList_004bf620[];
extern char s_igStringTable_className_004f5e78[];
extern char g_igStringTable_metaObject_005858b0[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igStringTable_InitFields();

void igStringTable_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igStringTable_metaObject_005858b0,   /* published MetaObject slot */
        igObject_Register,                     /* base class registrar */
        igObject_GetMetaObject_ParentAccessor, /* base class MetaObject accessor */
        thunk_igStringTable_GetMetaObject,     /* own MetaObject accessor (stored at +0x54) */
        s_igStringTable_className_004f5e78,    /* class name */
        0x18,                                  /* instance size */
        igStringTable_GetVTable,               /* vtable getter */
        &igStringTable_InitFields,             /* field adder */
        0,                                     /* extra callback item */
        g_igStringTable_callbackList_004bf620  /* callback list */
    );
}
