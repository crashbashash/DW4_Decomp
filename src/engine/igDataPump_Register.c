extern char igObject_GetMetaObject_ParentAccessor[];
extern char igDataPump_GetVTable[];
extern char thunk_igDataPump_GetMetaObject[];
extern char igObject_Register[];
extern char g_igDataPump_callbackList[];
extern char igDataPump_className[];
extern char g_igDataPump_metaObject[];
int DataPumpLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igDataPump_InitFields();

void igDataPump_Register(void) {
    DataPumpLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igDataPump_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igDataPump_GetMetaObject,
        igDataPump_className,
        0x1C, /* instance size */
        igDataPump_GetVTable,
        &igDataPump_InitFields,
        0, /* extra callback item */
        g_igDataPump_callbackList /* callback list */
    );
}
