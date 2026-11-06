extern char igNonRefCountedObjectList_GetPublishedMetaObject[];
extern char igVisualContextList_GetVTable[];
extern char thunk_igVisualContextList_GetMetaObject[];
extern char igNonRefCountedObjectList_Register[];
extern char g_igVisualContextList_callbackList[];
extern char igVisualContextList_className[];
extern char g_igVisualContextList_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();

void igVisualContextList_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igVisualContextList_metaObject,
        igNonRefCountedObjectList_Register,
        igNonRefCountedObjectList_GetPublishedMetaObject,
        thunk_igVisualContextList_GetMetaObject,
        igVisualContextList_className,
        0x14, /* instance size */
        igVisualContextList_GetVTable,
        0,
        0, /* extra callback item */
        g_igVisualContextList_callbackList /* callback list */
    );
}
