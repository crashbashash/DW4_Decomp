extern char igObjectList_GetPublishedMetaObject[];
extern char igMatrixObjectList_GetVTable[];
extern char thunk_igMatrixObjectList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igMatrixObjectList_callbackList[];
extern char igMatrixObjectList_className[];
extern char g_igMatrixObjectList_metaObject[];
int DataPumpLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igMatrixObjectList_Register(void) {
    DataPumpLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMatrixObjectList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igMatrixObjectList_GetMetaObject,
        igMatrixObjectList_className,
        0x14, /* instance size */
        igMatrixObjectList_GetVTable,
        0,
        0, /* extra callback item */
        g_igMatrixObjectList_callbackList /* callback list */
    );
}
