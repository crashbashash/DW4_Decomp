extern char igModel_GetPublishedMetaObject[];
extern char igModel_Register[];
extern char igViewModel_GetVTable[];
extern char thunk_igViewModel_GetMetaObject[];
extern char igViewModel_className[];
extern char g_igViewModel_metaObject[];
int igMetaObject_RegisterClass();
int ViewerLibrary_MarkRegistered();
int igViewModel_InitFields();

void igViewModel_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igViewModel_metaObject,
        igModel_Register,
        igModel_GetPublishedMetaObject,
        thunk_igViewModel_GetMetaObject,
        igViewModel_className,
        0xB0, /* instance size */
        igViewModel_GetVTable,
        &igViewModel_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
