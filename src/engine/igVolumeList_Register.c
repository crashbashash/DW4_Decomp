extern char igObjectList_GetPublishedMetaObject[];
extern char igVolumeList_GetVTable[];
extern char thunk_igVolumeList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igVolumeList_callbackList[];
extern char igVolumeList_className[];
extern char g_igVolumeList_metaObject[];
int FUN_00186a40();
int igMetaObject_RegisterClass();

void igVolumeList_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igVolumeList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igVolumeList_GetMetaObject,
        igVolumeList_className,
        0x14, /* instance size */
        igVolumeList_GetVTable,
        0,
        0, /* extra callback item */
        g_igVolumeList_callbackList /* callback list */
    );
}
