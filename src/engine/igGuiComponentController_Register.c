extern char igView_Register[];
extern char igView_GetPublishedMetaObject[];
extern char igGuiComponentController_GetVTable[];
extern char thunk_igGuiComponentController_GetMetaObject[];
extern char igGuiComponentController_className[];
extern char g_igGuiComponentController_metaObject[];
int igMetaObject_RegisterClass();
int GuiLibrary_MarkRegistered();

void igGuiComponentController_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igGuiComponentController_metaObject,
        igView_Register,
        igView_GetPublishedMetaObject,
        thunk_igGuiComponentController_GetMetaObject,
        igGuiComponentController_className,
        0xC, /* instance size */
        igGuiComponentController_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
