extern char igDataList_GetPublishedMetaObject[];
extern char igLongStack_GetVTable[];
extern char thunk_igLongStack_GetMetaObject[];
extern char igDataList_Register[];
extern char igLongStack_className[];
extern char g_igLongStack_metaObject[];
int DataPumpLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
extern int igLongStack_InitFields_001e4180[4];
void igLongStack_Register(void) {
    DataPumpLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igLongStack_metaObject,
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igLongStack_GetMetaObject,
        igLongStack_className,
        0x14, /* instance size */
        igLongStack_GetVTable,
        &igLongStack_InitFields_001e4180[0],
        0, /* extra callback item */
        0 /* callback list */
    );
}
