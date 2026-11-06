/* 0x002c2100 igLocationTable_Register: registers class igLocationTable with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igLocationTable_GetVTable[];
extern char thunk_igLocationTable_GetMetaObject[];
extern char igObject_Register[];
extern char g_igLocationTable_callbackList[];
extern char igLocationTable_className[];
extern char g_igLocationTable_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igLocationTable_InitFields();

void igLocationTable_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igLocationTable_metaObject, /* published MetaObject slot */
        igObject_Register,                     /* base class registrar */
        igObject_GetMetaObject_ParentAccessor, /* base class MetaObject accessor */
        thunk_igLocationTable_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igLocationTable_className,  /* class name */
        0x20,                                  /* instance size */
        igLocationTable_GetVTable,             /* vtable getter */
        &igLocationTable_InitFields,           /* field adder */
        0,                                     /* extra callback item */
        g_igLocationTable_callbackList  /* callback list */
    );
}
