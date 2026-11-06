extern char igObjectList_GetPublishedMetaObject[];
extern char igDataPumpList_GetVTable[];
extern char thunk_igDataPumpList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igDataPumpList_callbackList[];
extern char igDataPumpList_className[];
extern char g_igDataPumpList_metaObject[];
int DataPumpLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igDataPumpList_Register(void) {
    DataPumpLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igDataPumpList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igDataPumpList_GetMetaObject,
        igDataPumpList_className,
        0x14, /* instance size */
        igDataPumpList_GetVTable,
        0,
        0, /* extra callback item */
        g_igDataPumpList_callbackList /* callback list */
    );
}
