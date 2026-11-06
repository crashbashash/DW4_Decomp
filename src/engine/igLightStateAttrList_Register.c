extern char igObjectList_GetPublishedMetaObject[];
extern char igLightStateAttrList_GetVTable[];
extern char thunk_igLightStateAttrList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igLightStateAttrList_callbackList[];
extern char igLightStateAttrList_className[];
extern char g_igLightStateAttrList_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igLightStateAttrList_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igLightStateAttrList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igLightStateAttrList_GetMetaObject,
        igLightStateAttrList_className,
        0x14, /* instance size */
        igLightStateAttrList_GetVTable,
        0,
        0, /* extra callback item */
        g_igLightStateAttrList_callbackList /* callback list */
    );
}
