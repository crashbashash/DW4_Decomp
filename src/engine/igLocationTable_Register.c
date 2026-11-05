/* 0x002c2100 igLocationTable_Register: registers class igLocationTable with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igLocationTable_GetVTable[];
extern char thunk_igLocationTable_GetMetaObject[];
extern char igObject_Register[];
extern char g_igLocationTable_callbackList_004c0510[];
extern char s_igLocationTable_className_004f6f20[];
extern char g_igLocationTable_metaObject_00586078[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igLocationTable_InitFields();

void igLocationTable_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igLocationTable_metaObject_00586078, /* published MetaObject slot */
        igObject_Register,                     /* base class registrar */
        igObject_GetMetaObject_ParentAccessor, /* base class MetaObject accessor */
        thunk_igLocationTable_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igLocationTable_className_004f6f20,  /* class name */
        0x20,                                  /* instance size */
        igLocationTable_GetVTable,             /* vtable getter */
        &igLocationTable_InitFields,           /* field adder */
        0,                                     /* extra callback item */
        g_igLocationTable_callbackList_004c0510  /* callback list */
    );
}
