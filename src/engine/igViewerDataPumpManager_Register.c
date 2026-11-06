extern char igInfoManager_GetPublishedMetaObject[];
extern char igInfoManager_Register[];
extern char igViewerDataPumpManager_GetVTable[];
extern char thunk_igViewerDataPumpManager_GetMetaObject[];
extern char g_igViewerDataPumpManager_callbackList[];
extern char igViewerDataPumpManager_className[];
extern char g_igViewerDataPumpManager_metaObject[];
int igMetaObject_RegisterClass();
int ViewerLibrary_MarkRegistered();
extern int igViewerDataPumpManager_InitFields_0045c040[4];
void igViewerDataPumpManager_Register(void) {
    ViewerLibrary_MarkRegistered();  /* one-shot static-init latch (sets a gp-relative byte flag once) */
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igViewerDataPumpManager_metaObject,
        igInfoManager_Register,
        igInfoManager_GetPublishedMetaObject,
        thunk_igViewerDataPumpManager_GetMetaObject,
        igViewerDataPumpManager_className,
        0x14, /* instance size */
        igViewerDataPumpManager_GetVTable,
        &igViewerDataPumpManager_InitFields_0045c040[0],                              /* field adder: InitFields, registers the reflected fields */
        0, /* extra callback item */
        g_igViewerDataPumpManager_callbackList /* callback list */
    );
}
