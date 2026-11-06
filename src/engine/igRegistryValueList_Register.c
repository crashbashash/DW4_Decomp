extern char igObjectList_GetPublishedMetaObject[];
extern char igRegistryValueList_GetVTable[];
extern char thunk_igRegistryValueList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igRegistryValueList_callbackList[];
extern char igRegistryValueList_className[];
extern char g_igRegistryValueList_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igRegistryValueList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igRegistryValueList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igRegistryValueList_GetMetaObject,
        igRegistryValueList_className,
        0x14, /* instance size */
        igRegistryValueList_GetVTable,
        0,
        0, /* extra callback item */
        g_igRegistryValueList_callbackList /* callback list */
    );
}
