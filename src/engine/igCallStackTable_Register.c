extern char igObject_GetMetaObject_ParentAccessor[];
extern char igCallStackTable_GetVTable[];
extern char thunk_igCallStackTable_GetMetaObject[];
extern char igObject_Register[];
extern char g_igCallStackTable_callbackList[];
extern char igCallStackTable_className[];
extern char g_igCallStackTable_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igCallStackTable_InitFields();

void igCallStackTable_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igCallStackTable_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igCallStackTable_GetMetaObject,
        igCallStackTable_className,
        0x18, /* instance size */
        igCallStackTable_GetVTable,
        &igCallStackTable_InitFields,
        0, /* extra callback item */
        g_igCallStackTable_callbackList /* callback list */
    );
}
