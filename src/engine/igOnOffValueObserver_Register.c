extern char igView_Register[];
extern char igOnOffValueObserver_GetVTable[];
extern char thunk_igOnOffValueObserver_GetMetaObject[];
extern char igView_GetPublishedMetaObject[];
extern char g_igOnOffValueObserver_callbackList[];
extern char igOnOffValueObserver_className[];
extern char g_igOnOffValueObserver_metaObject[];
int igMetaObject_RegisterClass();
int GuiLibrary_MarkRegistered();
int igOnOffValueObserver_InitFields();

void igOnOffValueObserver_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igOnOffValueObserver_metaObject,
        igView_Register,
        igView_GetPublishedMetaObject,
        thunk_igOnOffValueObserver_GetMetaObject,
        igOnOffValueObserver_className,
        0x10, /* instance size */
        igOnOffValueObserver_GetVTable,
        &igOnOffValueObserver_InitFields,
        0, /* extra callback item */
        g_igOnOffValueObserver_callbackList /* callback list */
    );
}
