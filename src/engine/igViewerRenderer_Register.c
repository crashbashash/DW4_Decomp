extern char igRenderer_GetPublishedMetaObject[];
extern char igRenderer_Register[];
extern char igViewerRenderer_GetVTable[];
extern char thunk_igViewerRenderer_GetMetaObject[];
extern char g_igViewerRenderer_callbackList[];
extern char igViewerRenderer_className[];
extern char g_igViewerRenderer_metaObject[];
int igMetaObject_RegisterClass();
int ViewerLibrary_MarkRegistered();
int igViewerRenderer_InitFields();

void igViewerRenderer_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igViewerRenderer_metaObject,
        igRenderer_Register,
        igRenderer_GetPublishedMetaObject,
        thunk_igViewerRenderer_GetMetaObject,
        igViewerRenderer_className,
        0x5C, /* instance size */
        igViewerRenderer_GetVTable,
        &igViewerRenderer_InitFields,
        0, /* extra callback item */
        g_igViewerRenderer_callbackList /* callback list */
    );
}
