extern char igObjectList_GetPublishedMetaObject[];
extern char igObjectList_Register[];
extern char igObjectListList_GetVTable[];
extern char thunk_igObjectListList_GetMetaObject[];
extern char g_igObjectListList_callbackList[];
extern char igObjectListList_className[];
extern char g_igObjectListList_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igObjectListList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igObjectListList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igObjectListList_GetMetaObject,
        igObjectListList_className,
        0x14, /* instance size */
        igObjectListList_GetVTable,
        0,
        0, /* extra callback item */
        g_igObjectListList_callbackList /* callback list */
    );
}
