extern char igExternalImageEntry_GetVTable[];
extern char thunk_igExternalImageEntry_GetMetaObject_0014f750[];
extern char igExternalDirEntry_GetPublishedMetaObject[];
extern char igExternalDirEntry_Register[];
extern char igExternalImageEntry_className[];
extern char g_igExternalImageEntry_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();

void igExternalImageEntry_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igExternalImageEntry_metaObject,
        igExternalDirEntry_Register,
        igExternalDirEntry_GetPublishedMetaObject,
        thunk_igExternalImageEntry_GetMetaObject_0014f750,
        igExternalImageEntry_className,
        0x2C, /* instance size */
        igExternalImageEntry_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
