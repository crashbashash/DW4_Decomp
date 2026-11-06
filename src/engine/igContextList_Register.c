extern char igNonRefCountedObjectList_GetPublishedMetaObject[];
extern char igNonRefCountedObjectList_Register[];
extern char igContextList_GetVTable[];
extern char thunk_igContextList_GetMetaObject[];
extern char g_igContextList_callbackList[];
extern char igContextList_className[];
extern char g_igContextList_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igContextList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igContextList_metaObject,
        igNonRefCountedObjectList_Register,
        igNonRefCountedObjectList_GetPublishedMetaObject,
        thunk_igContextList_GetMetaObject,
        igContextList_className,
        0x14, /* instance size */
        igContextList_GetVTable,
        0,
        0, /* extra callback item */
        g_igContextList_callbackList /* callback list */
    );
}
