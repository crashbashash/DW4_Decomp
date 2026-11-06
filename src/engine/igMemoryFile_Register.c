extern char igMemoryFile_GetVTable[];
extern char thunk_igMemoryFile_GetMetaObject[];
extern char igFile_GetPublishedMetaObject[];
extern char thunk_FUN_002ef9a0[];
extern char igFile_Register[];
extern char igMemoryFile_className[];
extern char g_igMemoryFile_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igMemoryFile_InitFields();

void igMemoryFile_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMemoryFile_metaObject,
        igFile_Register,
        igFile_GetPublishedMetaObject,
        thunk_igMemoryFile_GetMetaObject,
        igMemoryFile_className,
        0x3C, /* instance size */
        igMemoryFile_GetVTable,
        &igMemoryFile_InitFields,
        thunk_FUN_002ef9a0, /* extra callback item */
        0 /* callback list */
    );
}
