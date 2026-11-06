extern char igInterfaceManager_Register[];
extern char igInterfaceManager_GetPublishedMetaObject[];
extern char igEventDispatcher_GetVTable[];
extern char thunk_igEventDispatcher_GetMetaObject[];
extern char g_igEventDispatcher_callbackList[];
extern char igEventDispatcher_className[];
extern char g_igEventDispatcher_metaObject[];
int igMetaObject_RegisterClass();
int GuiLibrary_MarkRegistered();
int igEventDispatcher_InitFields();

void igEventDispatcher_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igEventDispatcher_metaObject,
        igInterfaceManager_Register,
        igInterfaceManager_GetPublishedMetaObject,
        thunk_igEventDispatcher_GetMetaObject,
        igEventDispatcher_className,
        0x14, /* instance size */
        igEventDispatcher_GetVTable,
        &igEventDispatcher_InitFields,
        0, /* extra callback item */
        g_igEventDispatcher_callbackList /* callback list */
    );
}
