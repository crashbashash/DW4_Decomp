extern char igNamedObject_GetPublishedMetaObject[];
extern char igNamedObject_Register[];
extern char igMemoryFileEntry_GetVTable[];
extern char thunk_igMemoryFileEntry_GetMetaObject[];
extern char igMemoryFileEntry_className[];
extern char g_igMemoryFileEntry_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igMemoryFileEntry_InitFields();

void igMemoryFileEntry_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMemoryFileEntry_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        thunk_igMemoryFileEntry_GetMetaObject,
        igMemoryFileEntry_className,
        0x14, /* instance size */
        igMemoryFileEntry_GetVTable,
        &igMemoryFileEntry_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
