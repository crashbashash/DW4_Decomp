extern char igView_Register[];
extern char igView_GetPublishedMetaObject[];
extern char igRadioGroupSelectedObserver_GetVTable[];
extern char thunk_igRadioGroupSelectedObserver_GetMetaObject[];
extern char g_igRadioGroupSelectedObserver_callbackList[];
extern char igRadioGroupSelectedObserver_className[];
extern char g_igRadioGroupSelectedObserver_metaObject[];
int igMetaObject_RegisterClass();
int GuiLibrary_MarkRegistered();
int igRadioGroupSelectedObserver_InitFields();

void igRadioGroupSelectedObserver_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igRadioGroupSelectedObserver_metaObject,
        igView_Register,
        igView_GetPublishedMetaObject,
        thunk_igRadioGroupSelectedObserver_GetMetaObject,
        igRadioGroupSelectedObserver_className,
        0x10, /* instance size */
        igRadioGroupSelectedObserver_GetVTable,
        &igRadioGroupSelectedObserver_InitFields,
        0, /* extra callback item */
        g_igRadioGroupSelectedObserver_callbackList /* callback list */
    );
}
