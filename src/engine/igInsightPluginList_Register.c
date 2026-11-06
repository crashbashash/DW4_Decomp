extern char igObjectList_GetPublishedMetaObject[];
extern char igInsightPluginList_GetVTable[];
extern char thunk_igInsightPluginList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igInsightPluginList_callbackList[];
extern char igInsightPluginList_className[];
extern char g_igInsightPluginList_metaObject[];
int InsightLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igInsightPluginList_Register(void) {
    InsightLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igInsightPluginList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igInsightPluginList_GetMetaObject,
        igInsightPluginList_className,
        0x14, /* instance size */
        igInsightPluginList_GetVTable,
        0,
        0, /* extra callback item */
        g_igInsightPluginList_callbackList /* callback list */
    );
}
