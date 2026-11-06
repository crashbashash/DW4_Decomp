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
        0, /* abstract */
        g_igLocationTable_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igLocationTable_GetMetaObject,
        igLocationTable_className,
        0x20, /* instance size */
        igLocationTable_GetVTable,
        &igLocationTable_InitFields,
        0, /* extra callback item */
        g_igLocationTable_callbackList /* callback list */
    );
}
