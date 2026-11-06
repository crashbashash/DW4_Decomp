extern char igObjectList_GetPublishedMetaObject[];
extern char igThreadList_GetVTable[];
extern char thunk_igThreadList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igThreadList_callbackList[];
extern char igThreadList_className[];
extern char g_igThreadList_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igThreadList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igThreadList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igThreadList_GetMetaObject,
        igThreadList_className,
        0x14, /* instance size */
        igThreadList_GetVTable,
        0,
        0, /* extra callback item */
        g_igThreadList_callbackList /* callback list */
    );
}
