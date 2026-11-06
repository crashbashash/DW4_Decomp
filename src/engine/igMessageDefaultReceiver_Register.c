extern char igMessageReceiver_Register[];
extern char igMessageDefaultReceiver_GetVTable[];
extern char thunk_igMessageDefaultReceiver_GetMetaObject[];
extern char igMessageReceiver_GetPublishedMetaObject[];
extern char g_igMessageDefaultReceiver_callbackList[];
extern char igMessageDefaultReceiver_className[];
extern char g_igMessageDefaultReceiver_metaObject[];
int InsightLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igMessageDefaultReceiver_InitFields();

void igMessageDefaultReceiver_Register(void) {
    InsightLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMessageDefaultReceiver_metaObject,
        igMessageReceiver_Register,
        igMessageReceiver_GetPublishedMetaObject,
        thunk_igMessageDefaultReceiver_GetMetaObject,
        igMessageDefaultReceiver_className,
        0x18, /* instance size */
        igMessageDefaultReceiver_GetVTable,
        &igMessageDefaultReceiver_InitFields,
        0, /* extra callback item */
        g_igMessageDefaultReceiver_callbackList /* callback list */
    );
}
