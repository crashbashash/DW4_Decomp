extern char igObject_GetMetaObject_ParentAccessor[];
extern char igObject_Register[];
extern char igViewerGuiFactory_GetVTable[];
extern char thunk_igViewerGuiFactory_GetMetaObject[];
extern char g_igViewerGuiFactory_callbackList[];
extern char igViewerGuiFactory_className[];
extern char g_igViewerGuiFactory_metaObject[];
int igMetaObject_RegisterClass();
int ViewerLibrary_MarkRegistered();
int igViewerGuiFactory_InitFields();

void igViewerGuiFactory_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igViewerGuiFactory_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igViewerGuiFactory_GetMetaObject,
        igViewerGuiFactory_className,
        0x28, /* instance size */
        igViewerGuiFactory_GetVTable,
        &igViewerGuiFactory_InitFields,
        0, /* extra callback item */
        g_igViewerGuiFactory_callbackList /* callback list */
    );
}
