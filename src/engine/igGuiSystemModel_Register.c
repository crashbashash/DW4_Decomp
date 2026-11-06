extern char igModel_GetPublishedMetaObject[];
extern char igModel_Register[];
extern char igGuiSystemModel_GetVTable[];
extern char thunk_igGuiSystemModel_GetMetaObject[];
extern char g_igGuiSystemModel_callbackList[];
extern char igGuiSystemModel_className[];
extern char g_igGuiSystemModel_metaObject[];
int igMetaObject_RegisterClass();
int GuiLibrary_MarkRegistered();
int igGuiSystemModel_InitFields();

void igGuiSystemModel_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igGuiSystemModel_metaObject,
        igModel_Register,
        igModel_GetPublishedMetaObject,
        thunk_igGuiSystemModel_GetMetaObject,
        igGuiSystemModel_className,
        0xB8, /* instance size */
        igGuiSystemModel_GetVTable,
        &igGuiSystemModel_InitFields,
        0, /* extra callback item */
        g_igGuiSystemModel_callbackList /* callback list */
    );
}
