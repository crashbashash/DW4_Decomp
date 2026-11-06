extern char igObjectList_GetPublishedMetaObject[];
extern char igObjectList_Register[];
extern char igMediaList_GetVTable[];
extern char thunk_igMediaList_GetMetaObject[];
extern char g_igMediaList_callbackList[];
extern char igMediaList_className[];
extern char g_igMediaList_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igMediaList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMediaList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igMediaList_GetMetaObject,
        igMediaList_className,
        0x14, /* instance size */
        igMediaList_GetVTable,
        0,
        0, /* extra callback item */
        g_igMediaList_callbackList /* callback list */
    );
}
