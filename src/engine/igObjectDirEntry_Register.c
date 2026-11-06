extern char igObjectDirEntry_GetVTable[];
extern char thunk_igObjectDirEntry_GetMetaObject[];
extern char igDirEntry_GetPublishedMetaObject[];
extern char igDirEntry_Register[];
extern char g_igObjectDirEntry_callbackList[];
extern char igObjectDirEntry_className[];
extern char g_igObjectDirEntry_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igObjectDirEntry_InitFields();

void igObjectDirEntry_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igObjectDirEntry_metaObject,
        igDirEntry_Register,
        igDirEntry_GetPublishedMetaObject,
        thunk_igObjectDirEntry_GetMetaObject,
        igObjectDirEntry_className,
        0x34, /* instance size */
        igObjectDirEntry_GetVTable,
        &igObjectDirEntry_InitFields,
        0, /* extra callback item */
        g_igObjectDirEntry_callbackList /* callback list */
    );
}
