extern char igGroup_GetPublishedMetaObject[];
extern char igGroup_Register[];
extern char igGuiComponentNode_GetVTable[];
extern char thunk_igGuiComponentNode_GetMetaObject[];
extern char g_igGuiComponentNode_callbackList[];
extern char igGuiComponentNode_className[];
extern char g_igGuiComponentNode_metaObject[];
int igMetaObject_RegisterClass();
int GuiLibrary_MarkRegistered();
int igGuiComponentNode_InitFields();

void igGuiComponentNode_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igGuiComponentNode_metaObject,
        igGroup_Register,
        igGroup_GetPublishedMetaObject,
        thunk_igGuiComponentNode_GetMetaObject,
        igGuiComponentNode_className,
        0x24, /* instance size */
        igGuiComponentNode_GetVTable,
        &igGuiComponentNode_InitFields,
        0, /* extra callback item */
        g_igGuiComponentNode_callbackList /* callback list */
    );
}
