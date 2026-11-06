extern char igFolder_Register[];
extern char thunk_igPsx2Folder_GetMetaObject[];
extern char igPsx2Folder_GetVTable[];
extern char igFolder_GetPublishedMetaObject[];
extern char igPsx2Folder_className[];
extern char g_igPsx2Folder_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igPsx2Folder_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igPsx2Folder_metaObject,
        igFolder_Register,
        igFolder_GetPublishedMetaObject,
        thunk_igPsx2Folder_GetMetaObject,
        igPsx2Folder_className,
        0xC, /* instance size */
        igPsx2Folder_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
