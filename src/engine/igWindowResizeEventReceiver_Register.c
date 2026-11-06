extern char igWindowResizeEventReceiver_GetVTable[];
extern char thunk_igWindowResizeEventReceiver_GetMetaObject[];
extern char igEventReceiver_GetPublishedMetaObject[];
extern char igEventReceiver_Register[];
extern char g_igWindowResizeEventReceiver_callbackList[];
extern char igWindowResizeEventReceiver_className[];
extern char g_igWindowResizeEventReceiver_metaObject[];
int InsightLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igWindowResizeEventReceiver_InitFields();

void igWindowResizeEventReceiver_Register(void) {
    InsightLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igWindowResizeEventReceiver_metaObject,
        igEventReceiver_Register,
        igEventReceiver_GetPublishedMetaObject,
        thunk_igWindowResizeEventReceiver_GetMetaObject,
        igWindowResizeEventReceiver_className,
        0xC, /* instance size */
        igWindowResizeEventReceiver_GetVTable,
        &igWindowResizeEventReceiver_InitFields,
        0, /* extra callback item */
        g_igWindowResizeEventReceiver_callbackList /* callback list */
    );
}
