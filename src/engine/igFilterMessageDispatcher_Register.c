extern char igFilterMessageDispatcher_GetVTable[];
extern char thunk_igFilterMessageDispatcher_GetMetaObject[];
extern char igMessageDispatcher_GetPublishedMetaObject[];
extern char igMessageDispatcher_Register[];
extern char g_igFilterMessageDispatcher_callbackList[];
extern char igFilterMessageDispatcher_className[];
extern char g_igFilterMessageDispatcher_metaObject[];
int InsightLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igFilterMessageDispatcher_InitFields();

void igFilterMessageDispatcher_Register(void) {
    InsightLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igFilterMessageDispatcher_metaObject,
        igMessageDispatcher_Register,
        igMessageDispatcher_GetPublishedMetaObject,
        thunk_igFilterMessageDispatcher_GetMetaObject,
        igFilterMessageDispatcher_className,
        0x10, /* instance size */
        igFilterMessageDispatcher_GetVTable,
        &igFilterMessageDispatcher_InitFields,
        0, /* extra callback item */
        g_igFilterMessageDispatcher_callbackList /* callback list */
    );
}
