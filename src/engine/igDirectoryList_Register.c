extern char igObjectList_GetPublishedMetaObject[];
extern char igObjectList_Register[];
extern char igDirectoryList_GetVTable[];
extern char thunk_igDirectoryList_GetMetaObject[];
extern char g_igDirectoryList_callbackList[];
extern char igDirectoryList_className[];
extern char g_igDirectoryList_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igDirectoryList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igDirectoryList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igDirectoryList_GetMetaObject,
        igDirectoryList_className,
        0x14, /* instance size */
        igDirectoryList_GetVTable,
        0,
        0, /* extra callback item */
        g_igDirectoryList_callbackList /* callback list */
    );
}
