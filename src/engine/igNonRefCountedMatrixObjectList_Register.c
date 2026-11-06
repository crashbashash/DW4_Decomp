extern char igNonRefCountedObjectList_GetPublishedMetaObject[];
extern char igNonRefCountedMatrixObjectList_GetVTable[];
extern char thunk_igNonRefCountedMatrixObjectList_GetMetaObject[];
extern char igNonRefCountedObjectList_Register[];
extern char g_igNonRefCountedMatrixObjectList_callbackList[];
extern char igNonRefCountedMatrixObjectList_className[];
extern char g_igNonRefCountedMatrixObjectList_metaObject[];
int DataPumpLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igNonRefCountedMatrixObjectList_Register(void) {
    DataPumpLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igNonRefCountedMatrixObjectList_metaObject,
        igNonRefCountedObjectList_Register,
        igNonRefCountedObjectList_GetPublishedMetaObject,
        thunk_igNonRefCountedMatrixObjectList_GetMetaObject,
        igNonRefCountedMatrixObjectList_className,
        0x14, /* instance size */
        igNonRefCountedMatrixObjectList_GetVTable,
        0,
        0, /* extra callback item */
        g_igNonRefCountedMatrixObjectList_callbackList /* callback list */
    );
}
