extern char igObjectList_GetPublishedMetaObject[];
extern char igAABoxList_GetVTable[];
extern char thunk_igAABoxList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igAABoxList_callbackList[];
extern char igAABoxList_className[];
extern char g_igAABoxList_metaObject[];
int FUN_00186a40();
int igMetaObject_RegisterClass();

void igAABoxList_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igAABoxList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igAABoxList_GetMetaObject,
        igAABoxList_className,
        0x14, /* instance size */
        igAABoxList_GetVTable,
        0,
        0, /* extra callback item */
        g_igAABoxList_callbackList /* callback list */
    );
}
