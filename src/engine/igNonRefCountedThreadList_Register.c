extern char igNonRefCountedObjectList_GetPublishedMetaObject[];
extern char igNonRefCountedThreadList_GetVTable[];
extern char thunk_igNonRefCountedThreadList_GetMetaObject[];
extern char igNonRefCountedObjectList_Register[];
extern char g_igNonRefCountedThreadList_callbackList[];
extern char igNonRefCountedThreadList_className[];
extern char g_igNonRefCountedThreadList_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igNonRefCountedThreadList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igNonRefCountedThreadList_metaObject,
        igNonRefCountedObjectList_Register,
        igNonRefCountedObjectList_GetPublishedMetaObject,
        thunk_igNonRefCountedThreadList_GetMetaObject,
        igNonRefCountedThreadList_className,
        0x14, /* instance size */
        igNonRefCountedThreadList_GetVTable,
        0,
        0, /* extra callback item */
        g_igNonRefCountedThreadList_callbackList /* callback list */
    );
}
