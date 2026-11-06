extern char igObjectList_GetPublishedMetaObject[];
extern char igObjectList_Register[];
extern char igStatisticsItemList_GetVTable[];
extern char thunk_igStatisticsItemList_GetMetaObject[];
extern char g_igStatisticsItemList_callbackList[];
extern char igStatisticsItemList_className[];
extern char g_igStatisticsItemList_metaObject[];
int igMetaObject_RegisterClass();
int ViewerLibrary_MarkRegistered();

void igStatisticsItemList_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igStatisticsItemList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igStatisticsItemList_GetMetaObject,
        igStatisticsItemList_className,
        0x14, /* instance size */
        igStatisticsItemList_GetVTable,
        0,
        0, /* extra callback item */
        g_igStatisticsItemList_callbackList /* callback list */
    );
}
