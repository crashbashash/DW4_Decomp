extern char igView_Register[];
extern char igView_GetPublishedMetaObject[];
extern char igWindowSizeObserver_GetVTable[];
extern char thunk_igWindowSizeObserver_GetMetaObject[];
extern char igWindowSizeObserver_className[];
extern char g_igWindowSizeObserver_metaObject[];
int igMetaObject_RegisterClass();
int GuiLibrary_MarkRegistered();

void igWindowSizeObserver_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igWindowSizeObserver_metaObject,
        igView_Register,
        igView_GetPublishedMetaObject,
        thunk_igWindowSizeObserver_GetMetaObject,
        igWindowSizeObserver_className,
        0xC, /* instance size */
        igWindowSizeObserver_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
