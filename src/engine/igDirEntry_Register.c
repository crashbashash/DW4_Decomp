extern char igNamedObject_GetPublishedMetaObject[];
extern char igNamedObject_Register[];
extern char igDirEntry_GetVTable[];
extern char thunk_igDirEntry_GetMetaObject[];
extern char igDirEntry_className[];
extern char g_igDirEntry_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igDirEntry_InitFields();

void igDirEntry_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igDirEntry_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        thunk_igDirEntry_GetMetaObject,
        igDirEntry_className,
        0x1C, /* instance size */
        igDirEntry_GetVTable,
        &igDirEntry_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
