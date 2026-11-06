extern char igObjectList_GetPublishedMetaObject[];
extern char igInfoManagerList_GetVTable[];
extern char thunk_igInfoManagerList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igInfoManagerList_callbackList[];
extern char igInfoManagerList_className[];
extern char g_igInfoManagerList_metaObject[];
int InsightLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igInfoManagerList_Register(void) {
    InsightLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igInfoManagerList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igInfoManagerList_GetMetaObject,
        igInfoManagerList_className,
        0x14, /* instance size */
        igInfoManagerList_GetVTable,
        0,
        0, /* extra callback item */
        g_igInfoManagerList_callbackList /* callback list */
    );
}
