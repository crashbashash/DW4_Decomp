extern char igObjectList_GetPublishedMetaObject[];
extern char igObjectList_Register[];
extern char igMemoryFileEntryList_GetVTable[];
extern char thunk_igMemoryFileEntryList_GetMetaObject[];
extern char g_igMemoryFileEntryList_callbackList[];
extern char igMemoryFileEntryList_className[];
extern char g_igMemoryFileEntryList_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igMemoryFileEntryList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMemoryFileEntryList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igMemoryFileEntryList_GetMetaObject,
        igMemoryFileEntryList_className,
        0x14, /* instance size */
        igMemoryFileEntryList_GetVTable,
        0,
        0, /* extra callback item */
        g_igMemoryFileEntryList_callbackList /* callback list */
    );
}
