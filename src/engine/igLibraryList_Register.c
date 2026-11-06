extern char igObjectList_GetPublishedMetaObject[];
extern char igObjectList_Register[];
extern char igLibraryList_GetVTable[];
extern char thunk_igLibraryList_GetMetaObject[];
extern char g_igLibraryList_callbackList[];
extern char igLibraryList_className[];
extern char g_igLibraryList_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igLibraryList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igLibraryList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igLibraryList_GetMetaObject,
        igLibraryList_className,
        0x14, /* instance size */
        igLibraryList_GetVTable,
        0,
        0, /* extra callback item */
        g_igLibraryList_callbackList /* callback list */
    );
}
