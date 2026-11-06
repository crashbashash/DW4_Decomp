extern char igObjectList_GetPublishedMetaObject[];
extern char igObjectList_Register[];
extern char igMemoryPoolInfoList_GetVTable[];
extern char thunk_igMemoryPoolInfoList_GetMetaObject[];
extern char g_igMemoryPoolInfoList_callbackList[];
extern char igMemoryPoolInfoList_className[];
extern char g_igMemoryPoolInfoList_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igMemoryPoolInfoList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMemoryPoolInfoList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igMemoryPoolInfoList_GetMetaObject,
        igMemoryPoolInfoList_className,
        0x14, /* instance size */
        igMemoryPoolInfoList_GetVTable,
        0,
        0, /* extra callback item */
        g_igMemoryPoolInfoList_callbackList /* callback list */
    );
}
