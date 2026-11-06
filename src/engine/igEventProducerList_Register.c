extern char igObjectList_GetPublishedMetaObject[];
extern char igEventProducerList_GetVTable[];
extern char thunk_igEventProducerList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igEventProducerList_callbackList[];
extern char igEventProducerList_className[];
extern char g_igEventProducerList_metaObject[];
int WindowInputLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igEventProducerList_Register(void) {
    WindowInputLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igEventProducerList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igEventProducerList_GetMetaObject,
        igEventProducerList_className,
        0x14, /* instance size */
        igEventProducerList_GetVTable,
        0,
        0, /* extra callback item */
        g_igEventProducerList_callbackList /* callback list */
    );
}
