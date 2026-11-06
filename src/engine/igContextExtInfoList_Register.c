extern char igObjectList_GetPublishedMetaObject[];
extern char igObjectList_Register[];
extern char igContextExtInfoList_GetVTable[];
extern char thunk_igContextExtInfoList_GetMetaObject[];
extern char g_igContextExtInfoList_callbackList[];
extern char igContextExtInfoList_className[];
extern char g_igContextExtInfoList_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igContextExtInfoList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igContextExtInfoList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igContextExtInfoList_GetMetaObject,
        igContextExtInfoList_className,
        0x14, /* instance size */
        igContextExtInfoList_GetVTable,
        0,
        0, /* extra callback item */
        g_igContextExtInfoList_callbackList /* callback list */
    );
}
