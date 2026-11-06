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
        0, /* abstract */
        g_igSymbolTable_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igSymbolTable_GetMetaObject,
        igSymbolTable_className,
        0x2C, /* instance size */
        igSymbolTable_GetVTable,
        &igSymbolTable_InitFields,
        0, /* extra callback item */
        g_igSymbolTable_callbackList /* callback list */
    );
}
