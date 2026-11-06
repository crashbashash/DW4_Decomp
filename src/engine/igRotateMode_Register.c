extern char igViewMode_GetPublishedMetaObject[];
extern char igRotateMode_GetVTable[];
extern char thunk_igRotateMode_GetMetaObject[];
extern char igViewMode_Register[];
extern char igRotateMode_className[];
extern char g_igRotateMode_metaObject[];
int igMetaObject_RegisterClass();
int ViewerLibrary_MarkRegistered();
int igRotateMode_InitFields();

void igRotateMode_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igRotateMode_metaObject,
        igViewMode_Register,
        igViewMode_GetPublishedMetaObject,
        thunk_igRotateMode_GetMetaObject,
        igRotateMode_className,
        0x94, /* instance size */
        igRotateMode_GetVTable,
        &igRotateMode_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
