extern char igEventReceiver_GetPublishedMetaObject[];
extern char igGuiSystem_GetVTable[];
extern char thunk_igGuiSystem_GetMetaObject[];
extern char igEventReceiver_Register[];
extern char g_igGuiSystem_callbackList[];
extern char igGuiSystem_className[];
extern char g_igGuiSystem_metaObject[];
int igMetaObject_RegisterClass();
int GuiLibrary_MarkRegistered();
int igGuiSystem_InitFields();

void igGuiSystem_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igGuiSystem_metaObject,
        igEventReceiver_Register,
        igEventReceiver_GetPublishedMetaObject,
        thunk_igGuiSystem_GetMetaObject,
        igGuiSystem_className,
        0x24, /* instance size */
        igGuiSystem_GetVTable,
        &igGuiSystem_InitFields,
        0, /* extra callback item */
        g_igGuiSystem_callbackList /* callback list */
    );
}
