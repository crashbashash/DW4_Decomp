extern char igObjectList_GetPublishedMetaObject[];
extern char igObjectList_Register[];
extern char igInfoList_GetVTable[];
extern char thunk_igInfoList_GetMetaObject[];
extern char g_igInfoList_callbackList[];
extern char igInfoList_className[];
extern char g_igInfoList_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igInfoList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igInfoList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igInfoList_GetMetaObject,
        igInfoList_className,
        0x14, /* instance size */
        igInfoList_GetVTable,
        0,
        0, /* extra callback item */
        g_igInfoList_callbackList /* callback list */
    );
}
