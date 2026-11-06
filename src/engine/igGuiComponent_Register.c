extern char igObject_GetMetaObject_ParentAccessor[];
extern char igObject_Register[];
extern char igGuiComponent_GetVTable[];
extern char thunk_igGuiComponent_GetMetaObject[];
extern char g_igGuiComponent_callbackList[];
extern char igGuiComponent_className[];
extern char g_igGuiComponent_metaObject[];
int igMetaObject_RegisterClass();
int GuiLibrary_MarkRegistered();
int igGuiComponent_InitFields();

void igGuiComponent_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igGuiComponent_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igGuiComponent_GetMetaObject,
        igGuiComponent_className,
        0x24, /* instance size */
        igGuiComponent_GetVTable,
        &igGuiComponent_InitFields,
        0, /* extra callback item */
        g_igGuiComponent_callbackList /* callback list */
    );
}
