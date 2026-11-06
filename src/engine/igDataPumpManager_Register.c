extern char igObject_GetMetaObject_ParentAccessor[];
extern char igDataPumpManager_GetVTable[];
extern char thunk_igDataPumpManager_GetMetaObject[];
extern char igObject_Register[];
extern char g_igDataPumpManager_callbackList[];
extern char igDataPumpManager_className[];
extern char g_igDataPumpManager_metaObject[];
int DataPumpLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igDataPumpManager_InitFields();

void igDataPumpManager_Register(void) {
    DataPumpLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igDataPumpManager_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igDataPumpManager_GetMetaObject,
        igDataPumpManager_className,
        0xC, /* instance size */
        igDataPumpManager_GetVTable,
        &igDataPumpManager_InitFields,
        0, /* extra callback item */
        g_igDataPumpManager_callbackList /* callback list */
    );
}
