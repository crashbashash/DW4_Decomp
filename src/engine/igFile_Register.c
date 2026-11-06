extern char igNamedObject_GetPublishedMetaObject[];
extern char igNamedObject_Register[];
extern char thunk_igFile_GetMetaObject[];
extern char igFile_className[];
extern char g_igFile_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igFile_InitFields();

void igFile_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igFile_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        thunk_igFile_GetMetaObject,
        igFile_className,
        0x2C, /* instance size */
        0,
        &igFile_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
