extern char igObjectList_GetPublishedMetaObject[];
extern char igMessageFilterList_GetVTable[];
extern char thunk_igMessageFilterList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igMessageFilterList_callbackList[];
extern char igMessageFilterList_className[];
extern char g_igMessageFilterList_metaObject[];
int InsightLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igMessageFilterList_Register(void) {
    InsightLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMessageFilterList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igMessageFilterList_GetMetaObject,
        igMessageFilterList_className,
        0x14, /* instance size */
        igMessageFilterList_GetVTable,
        0,
        0, /* extra callback item */
        g_igMessageFilterList_callbackList /* callback list */
    );
}
