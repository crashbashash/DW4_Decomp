extern char igGuiComponentAspect_GetPublishedMetaObject[];
extern char igGuiComponentAspect_Register[];
extern char igDefaultAspect_GetVTable[];
extern char thunk_igDefaultAspect_GetMetaObject[];
extern char g_igDefaultAspect_callbackList[];
extern char igDefaultAspect_className[];
extern char g_igDefaultAspect_metaObject[];
int igMetaObject_RegisterClass();
int GuiLibrary_MarkRegistered();
int igDefaultAspect_InitFields();

void igDefaultAspect_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igDefaultAspect_metaObject,
        igGuiComponentAspect_Register,
        igGuiComponentAspect_GetPublishedMetaObject,
        thunk_igDefaultAspect_GetMetaObject,
        igDefaultAspect_className,
        0x2C, /* instance size */
        igDefaultAspect_GetVTable,
        &igDefaultAspect_InitFields,
        0, /* extra callback item */
        g_igDefaultAspect_callbackList /* callback list */
    );
}
