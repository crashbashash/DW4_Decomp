extern char igObjectList_GetPublishedMetaObject[];
extern char igMessageReceiverList_GetVTable[];
extern char thunk_igMessageReceiverList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igMessageReceiverList_callbackList[];
extern char igMessageReceiverList_className[];
extern char g_igMessageReceiverList_metaObject[];
int InsightLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igMessageReceiverList_Register(void) {
    InsightLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMessageReceiverList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igMessageReceiverList_GetMetaObject,
        igMessageReceiverList_className,
        0x14, /* instance size */
        igMessageReceiverList_GetVTable,
        0,
        0, /* extra callback item */
        g_igMessageReceiverList_callbackList /* callback list */
    );
}
