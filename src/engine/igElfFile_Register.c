extern char igProgramFile_Register[];
extern char thunk_igElfFile_GetMetaObject[];
extern char igElfFile_GetVTable[];
extern char igProgramFile_GetPublishedMetaObject[];
extern char igElfFile_className[];
extern char g_igElfFile_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igElfFile_InitFields();

void igElfFile_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igElfFile_metaObject,
        igProgramFile_Register,
        igProgramFile_GetPublishedMetaObject,
        thunk_igElfFile_GetMetaObject,
        igElfFile_className,
        0x64, /* instance size */
        igElfFile_GetVTable,
        &igElfFile_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
