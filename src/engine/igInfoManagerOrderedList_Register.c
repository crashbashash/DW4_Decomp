extern char igInfoManagerOrderedList_GetVTable[];
extern char thunk_igInfoManagerOrderedList_GetMetaObject[];
extern char igDependencyOrderedList_GetPublishedMetaObject[];
extern char igDependencyOrderedList_Register[];
extern char g_igInfoManagerOrderedList_callbackList[];
extern char igInfoManagerOrderedList_className[];
extern char g_igInfoManagerOrderedList_metaObject[];
int InsightLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igInfoManagerOrderedList_Register(void) {
    InsightLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igInfoManagerOrderedList_metaObject,
        igDependencyOrderedList_Register,
        igDependencyOrderedList_GetPublishedMetaObject,
        thunk_igInfoManagerOrderedList_GetMetaObject,
        igInfoManagerOrderedList_className,
        0x1C, /* instance size */
        igInfoManagerOrderedList_GetVTable,
        0,
        0, /* extra callback item */
        g_igInfoManagerOrderedList_callbackList /* callback list */
    );
}
