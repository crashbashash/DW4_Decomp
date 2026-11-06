extern char igObjectList_GetPublishedMetaObject[];
extern char igLightList_GetVTable[];
extern char thunk_igLightList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igLightList_callbackList[];
extern char igLightList_className[];
extern char g_igLightList_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igLightList_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igLightList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igLightList_GetMetaObject,
        igLightList_className,
        0x14, /* instance size */
        igLightList_GetVTable,
        0,
        0, /* extra callback item */
        g_igLightList_callbackList /* callback list */
    );
}
