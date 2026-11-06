extern char igEventReceiver_GetPublishedMetaObject[];
extern char igHotKeyEventReceiver_GetVTable[];
extern char thunk_igHotKeyEventReceiver_GetMetaObject[];
extern char igEventReceiver_Register[];
extern char g_igHotKeyEventReceiver_callbackList[];
extern char igHotKeyEventReceiver_className[];
extern char g_igHotKeyEventReceiver_metaObject[];
int igMetaObject_RegisterClass();
int GuiLibrary_MarkRegistered();
int igHotKeyEventReceiver_InitFields();

void igHotKeyEventReceiver_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igHotKeyEventReceiver_metaObject,
        igEventReceiver_Register,
        igEventReceiver_GetPublishedMetaObject,
        thunk_igHotKeyEventReceiver_GetMetaObject,
        igHotKeyEventReceiver_className,
        0xC, /* instance size */
        igHotKeyEventReceiver_GetVTable,
        &igHotKeyEventReceiver_InitFields,
        0, /* extra callback item */
        g_igHotKeyEventReceiver_callbackList /* callback list */
    );
}
