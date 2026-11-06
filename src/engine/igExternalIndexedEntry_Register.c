extern char igDirEntry_GetPublishedMetaObject[];
extern char igExternalIndexedEntry_GetVTable[];
extern char thunk_igExternalIndexedEntry_GetMetaObject[];
extern char igDirEntry_Register[];
extern char g_igExternalIndexedEntry_callbackList[];
extern char igExternalIndexedEntry_className[];
extern char g_igExternalIndexedEntry_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igExternalIndexedEntry_InitFields();

void igExternalIndexedEntry_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igExternalIndexedEntry_metaObject,
        igDirEntry_Register,
        igDirEntry_GetPublishedMetaObject,
        thunk_igExternalIndexedEntry_GetMetaObject,
        igExternalIndexedEntry_className,
        0x34, /* instance size */
        igExternalIndexedEntry_GetVTable,
        &igExternalIndexedEntry_InitFields,
        0, /* extra callback item */
        g_igExternalIndexedEntry_callbackList /* callback list */
    );
}
