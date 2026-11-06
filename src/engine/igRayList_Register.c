extern char igObjectList_GetPublishedMetaObject[];
extern char igRayList_GetVTable[];
extern char thunk_igRayList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igRayList_callbackList[];
extern char igRayList_className[];
extern char g_igRayList_metaObject[];
int FUN_00186a40();
int igMetaObject_RegisterClass();

void igRayList_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igRayList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igRayList_GetMetaObject,
        igRayList_className,
        0x14, /* instance size */
        igRayList_GetVTable,
        0,
        0, /* extra callback item */
        g_igRayList_callbackList /* callback list */
    );
}
