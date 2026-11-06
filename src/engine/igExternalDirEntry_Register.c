extern char igDirEntry_GetPublishedMetaObject[];
extern char igExternalDirEntry_GetVTable[];
extern char thunk_igExternalDirEntry_GetMetaObject[];
extern char igDirEntry_Register[];
extern char g_igExternalDirEntry_callbackList[];
extern char igExternalDirEntry_className[];
extern char g_igExternalDirEntry_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
void FUN_002c55f0(void);
void igExternalDirEntry_Register(void) {
    FUN_002b5d50();  /* Set-once guard that first runs the sibling registrars it chains to. */
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igExternalDirEntry_metaObject,
        igDirEntry_Register,
        igDirEntry_GetPublishedMetaObject,
        thunk_igExternalDirEntry_GetMetaObject,
        igExternalDirEntry_className,
        0x2C, /* instance size */
        igExternalDirEntry_GetVTable,
        FUN_002c55f0,
        0,                                          /* static-initializer callback item (appended on fresh configuration) */
        g_igExternalDirEntry_callbackList  /* 0-terminated dependency-callback list */
    );
}
