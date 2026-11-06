/* 0x002b87d0 igSymbolTable_Register: registers class igSymbolTable with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igSymbolTable_GetVTable[];
extern char thunk_igSymbolTable_GetMetaObject[];
extern char igObject_Register[];
extern char g_igSymbolTable_callbackList[];
extern char igSymbolTable_className[];
extern char g_igSymbolTable_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igSymbolTable_InitFields();

void igSymbolTable_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igSymbolTable_metaObject,   /* published MetaObject slot */
        igObject_Register,                     /* base class registrar */
        igObject_GetMetaObject_ParentAccessor, /* base class MetaObject accessor */
        thunk_igSymbolTable_GetMetaObject,     /* own MetaObject accessor (stored at +0x54) */
        igSymbolTable_className,    /* class name */
        0x2C,                                  /* instance size */
        igSymbolTable_GetVTable,               /* vtable getter */
        &igSymbolTable_InitFields,             /* field adder */
        0,                                     /* extra callback item */
        g_igSymbolTable_callbackList  /* callback list */
    );
}
