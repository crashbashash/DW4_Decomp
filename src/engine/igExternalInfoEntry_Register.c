extern char igDirEntry_GetPublishedMetaObject[];
extern char igExternalInfoEntry_GetVTable[];
extern char thunk_igExternalInfoEntry_GetMetaObject[];
extern char igDirEntry_Register[];
extern char igExternalInfoEntry_className[];
extern char g_igExternalInfoEntry_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igExternalInfoEntry_InitFields();

void igExternalInfoEntry_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igExternalInfoEntry_metaObject,
        igDirEntry_Register,
        igDirEntry_GetPublishedMetaObject,
        thunk_igExternalInfoEntry_GetMetaObject,
        igExternalInfoEntry_className,
        0x28, /* instance size */
        igExternalInfoEntry_GetVTable,
        &igExternalInfoEntry_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
