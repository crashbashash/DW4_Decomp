extern char igView_Register[];
extern char igView_GetPublishedMetaObject[];
extern char igStatisticsItem_GetVTable[];
extern char thunk_igStatisticsItem_GetMetaObject[];
extern char g_igStatisticsItem_callbackList[];
extern char igStatisticsItem_className[];
extern char g_igStatisticsItem_metaObject[];
int igMetaObject_RegisterClass();
int ViewerLibrary_MarkRegistered();
int igStatisticsItem_InitFields();

void igStatisticsItem_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igStatisticsItem_metaObject,
        igView_Register,
        igView_GetPublishedMetaObject,
        thunk_igStatisticsItem_GetMetaObject,
        igStatisticsItem_className,
        0x3C, /* instance size */
        igStatisticsItem_GetVTable,
        &igStatisticsItem_InitFields,
        0, /* extra callback item */
        g_igStatisticsItem_callbackList /* callback list */
    );
}
