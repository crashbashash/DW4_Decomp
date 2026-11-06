extern char igObjectList_GetPublishedMetaObject[];
extern char igObjectList_Register[];
extern char igGuiComponentList_GetVTable[];
extern char thunk_igGuiComponentList_GetMetaObject[];
extern char g_igGuiComponentList_callbackList[];
extern char igGuiComponentList_className[];
extern char g_igGuiComponentList_metaObject[];
int igMetaObject_RegisterClass();
int GuiLibrary_MarkRegistered();

void igGuiComponentList_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igGuiComponentList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igGuiComponentList_GetMetaObject,
        igGuiComponentList_className,
        0x14, /* instance size */
        igGuiComponentList_GetVTable,
        0,
        0, /* extra callback item */
        g_igGuiComponentList_callbackList /* callback list */
    );
}
