extern char igView_Register[];
extern char igView_GetPublishedMetaObject[];
extern char igActiveComponentsObserver_GetVTable[];
extern char thunk_igActiveComponentsObserver_GetMetaObject[];
extern char g_igActiveComponentsObserver_callbackList[];
extern char igActiveComponentsObserver_className[];
extern char g_igActiveComponentsObserver_metaObject[];
int igMetaObject_RegisterClass();
int GuiLibrary_MarkRegistered();
int igActiveComponentsObserver_InitFields();

void igActiveComponentsObserver_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igActiveComponentsObserver_metaObject,
        igView_Register,
        igView_GetPublishedMetaObject,
        thunk_igActiveComponentsObserver_GetMetaObject,
        igActiveComponentsObserver_className,
        0x18, /* instance size */
        igActiveComponentsObserver_GetVTable,
        &igActiveComponentsObserver_InitFields,
        0, /* extra callback item */
        g_igActiveComponentsObserver_callbackList /* callback list */
    );
}
