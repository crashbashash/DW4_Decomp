extern char igView_Register[];
extern char igView_GetPublishedMetaObject[];
extern char igViewMode_GetVTable[];
extern char thunk_igViewMode_GetMetaObject[];
extern char igViewMode_className[];
extern char g_igViewMode_metaObject[];
int igMetaObject_RegisterClass();
int ViewerLibrary_MarkRegistered();
int igViewMode_InitFields();

void igViewMode_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igViewMode_metaObject,
        igView_Register,
        igView_GetPublishedMetaObject,
        thunk_igViewMode_GetMetaObject,
        igViewMode_className,
        0x4C, /* instance size */
        igViewMode_GetVTable,
        &igViewMode_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
