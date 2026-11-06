extern char igObject_GetMetaObject_ParentAccessor[];
extern char igStringTable_GetVTable[];
extern char thunk_igStringTable_GetMetaObject[];
extern char igObject_Register[];
extern char g_igStringTable_callbackList[];
extern char igStringTable_className[];
extern char g_igStringTable_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igStringTable_InitFields();

void igStringTable_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igStringTable_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igStringTable_GetMetaObject,
        igStringTable_className,
        0x18, /* instance size */
        igStringTable_GetVTable,
        &igStringTable_InitFields,
        0, /* extra callback item */
        g_igStringTable_callbackList /* callback list */
    );
}
