extern char igDirEntry_GetPublishedMetaObject[];
extern char igMemoryDirEntry_GetVTable[];
extern char thunk_igMemoryDirEntry_GetMetaObject[];
extern char igDirEntry_Register[];
extern char g_igMemoryDirEntry_callbackList[];
extern char igMemoryDirEntry_className[];
extern char g_igMemoryDirEntry_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igMemoryDirEntry_InitFields();

void igMemoryDirEntry_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMemoryDirEntry_metaObject,
        igDirEntry_Register,
        igDirEntry_GetPublishedMetaObject,
        thunk_igMemoryDirEntry_GetMetaObject,
        igMemoryDirEntry_className,
        0x38, /* instance size */
        igMemoryDirEntry_GetVTable,
        &igMemoryDirEntry_InitFields,
        0, /* extra callback item */
        g_igMemoryDirEntry_callbackList /* callback list */
    );
}
