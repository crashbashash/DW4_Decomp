extern char igView_Register[];
extern char igView_GetPublishedMetaObject[];
extern char igMousePosObserver_GetVTable[];
extern char thunk_igMousePosObserver_GetMetaObject[];
extern char g_igMousePosObserver_callbackList[];
extern char igMousePosObserver_className[];
extern char g_igMousePosObserver_metaObject[];
int igMetaObject_RegisterClass();
int GuiLibrary_MarkRegistered();
int igMousePosObserver_InitFields();

void igMousePosObserver_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMousePosObserver_metaObject,
        igView_Register,
        igView_GetPublishedMetaObject,
        thunk_igMousePosObserver_GetMetaObject,
        igMousePosObserver_className,
        0x64, /* instance size */
        igMousePosObserver_GetVTable,
        &igMousePosObserver_InitFields,
        0, /* extra callback item */
        g_igMousePosObserver_callbackList /* callback list */
    );
}
