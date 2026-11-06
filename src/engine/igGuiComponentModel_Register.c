extern char igModel_GetPublishedMetaObject[];
extern char igModel_Register[];
extern char igGuiComponentModel_GetVTable[];
extern char thunk_igGuiComponentModel_GetMetaObject[];
extern char g_igGuiComponentModel_callbackList[];
extern char igGuiComponentModel_className[];
extern char g_igGuiComponentModel_metaObject[];
int igMetaObject_RegisterClass();
int GuiLibrary_MarkRegistered();
int igGuiComponentModel_InitFields();

void igGuiComponentModel_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igGuiComponentModel_metaObject,
        igModel_Register,
        igModel_GetPublishedMetaObject,
        thunk_igGuiComponentModel_GetMetaObject,
        igGuiComponentModel_className,
        0x24, /* instance size */
        igGuiComponentModel_GetVTable,
        &igGuiComponentModel_InitFields,
        0, /* extra callback item */
        g_igGuiComponentModel_callbackList /* callback list */
    );
}
