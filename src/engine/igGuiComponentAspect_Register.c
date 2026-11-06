extern char igView_Register[];
extern char igView_GetPublishedMetaObject[];
extern char thunk_igGuiComponentAspect_GetMetaObject[];
extern char g_igGuiComponentAspect_callbackList[];
extern char igGuiComponentAspect_className[];
extern char g_igGuiComponentAspect_metaObject[];
int igMetaObject_RegisterClass();
int GuiLibrary_MarkRegistered();
int igGuiComponentAspect_InitFields();

void igGuiComponentAspect_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igGuiComponentAspect_metaObject,
        igView_Register,
        igView_GetPublishedMetaObject,
        thunk_igGuiComponentAspect_GetMetaObject,
        igGuiComponentAspect_className,
        0x28, /* instance size */
        0,
        &igGuiComponentAspect_InitFields,
        0, /* extra callback item */
        g_igGuiComponentAspect_callbackList /* callback list */
    );
}
