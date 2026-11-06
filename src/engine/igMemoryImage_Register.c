extern char thunk_igMemoryImage_GetMetaObject[];
extern char igImage_GetPublishedMetaObject[];
extern char igImage_Register[];
extern char igMemoryImage_className[];
extern char g_igMemoryImage_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();

void igMemoryImage_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igMemoryImage_metaObject,
        igImage_Register,
        igImage_GetPublishedMetaObject,
        thunk_igMemoryImage_GetMetaObject,
        igMemoryImage_className,
        0x5C, /* instance size */
        0,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
