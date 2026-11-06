extern char igObject_GetMetaObject_ParentAccessor[];
extern char igObject_Register[];
extern char igViewerStatisticsManager_GetVTable[];
extern char thunk_igViewerStatisticsManager_GetMetaObject[];
extern char g_igViewerStatisticsManager_callbackList[];
extern char igViewerStatisticsManager_className[];
extern char g_igViewerStatisticsManager_metaObject[];
int igMetaObject_RegisterClass();
int ViewerLibrary_MarkRegistered();
int igViewerStatisticsManager_InitFields();

void igViewerStatisticsManager_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igViewerStatisticsManager_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igViewerStatisticsManager_GetMetaObject,
        igViewerStatisticsManager_className,
        0x48, /* instance size */
        igViewerStatisticsManager_GetVTable,
        &igViewerStatisticsManager_InitFields,
        0, /* extra callback item */
        g_igViewerStatisticsManager_callbackList /* callback list */
    );
}
