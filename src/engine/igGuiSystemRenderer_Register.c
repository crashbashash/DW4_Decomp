extern char igRenderer_GetPublishedMetaObject[];
extern char igRenderer_Register[];
extern char igGuiSystemRenderer_GetVTable[];
extern char thunk_igGuiSystemRenderer_GetMetaObject[];
extern char g_igGuiSystemRenderer_callbackList[];
extern char igGuiSystemRenderer_className[];
extern char g_igGuiSystemRenderer_metaObject[];
int igMetaObject_RegisterClass();
int GuiLibrary_MarkRegistered();
int igGuiSystemRenderer_InitFields();

void igGuiSystemRenderer_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igGuiSystemRenderer_metaObject,
        igRenderer_Register,
        igRenderer_GetPublishedMetaObject,
        thunk_igGuiSystemRenderer_GetMetaObject,
        igGuiSystemRenderer_className,
        0x1C, /* instance size */
        igGuiSystemRenderer_GetVTable,
        &igGuiSystemRenderer_InitFields,
        0, /* extra callback item */
        g_igGuiSystemRenderer_callbackList /* callback list */
    );
}
