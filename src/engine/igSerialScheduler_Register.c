extern char igSerialScheduler_GetVTable[];
extern char thunk_igSerialScheduler_GetMetaObject[];
extern char igInsightScheduler_GetPublishedMetaObject[];
extern char igInsightScheduler_Register[];
extern char g_igSerialScheduler_callbackList[];
extern char igSerialScheduler_className[];
extern char g_igSerialScheduler_metaObject[];
int InsightLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igSerialScheduler_InitFields();

void igSerialScheduler_Register(void) {
    InsightLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igSerialScheduler_metaObject,
        igInsightScheduler_Register,
        igInsightScheduler_GetPublishedMetaObject,
        thunk_igSerialScheduler_GetMetaObject,
        igSerialScheduler_className,
        0x10, /* instance size */
        igSerialScheduler_GetVTable,
        &igSerialScheduler_InitFields,
        0, /* extra callback item */
        g_igSerialScheduler_callbackList /* callback list */
    );
}
