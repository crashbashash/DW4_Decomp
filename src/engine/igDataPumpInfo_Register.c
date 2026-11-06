extern char igInfo_GetPublishedMetaObject[];
extern char igDataPumpInfo_GetVTable[];
extern char thunk_igDataPumpInfo_GetMetaObject[];
extern char igInfo_Register[];
extern char g_igDataPumpInfo_callbackList[];
extern char igDataPumpInfo_className[];
extern char g_igDataPumpInfo_metaObject[];
int DataPumpLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igDataPumpInfo_InitFields();

void igDataPumpInfo_Register(void) {
    DataPumpLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igDataPumpInfo_metaObject,
        igInfo_Register,
        igInfo_GetPublishedMetaObject,
        thunk_igDataPumpInfo_GetMetaObject,
        igDataPumpInfo_className,
        0x18, /* instance size */
        igDataPumpInfo_GetVTable,
        &igDataPumpInfo_InitFields,
        0, /* extra callback item */
        g_igDataPumpInfo_callbackList /* callback list */
    );
}
