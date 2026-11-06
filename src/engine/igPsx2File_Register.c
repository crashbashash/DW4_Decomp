extern char igFile_GetPublishedMetaObject[];
extern char igFile_Register[];
extern char thunk_igPsx2File_GetMetaObject[];
extern char igPsx2File_GetVTable[];
extern char thunk_FUN_0032c0c0[];
extern char igPsx2File_className[];
extern char g_igPsx2File_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igPsx2File_InitFields();

void igPsx2File_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igPsx2File_metaObject,
        igFile_Register,
        igFile_GetPublishedMetaObject,
        thunk_igPsx2File_GetMetaObject,
        igPsx2File_className,
        0x4C, /* instance size */
        igPsx2File_GetVTable,
        &igPsx2File_InitFields,
        thunk_FUN_0032c0c0, /* extra callback item */
        0 /* callback list */
    );
}
