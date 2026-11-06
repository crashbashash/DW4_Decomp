extern char igObjectList_GetPublishedMetaObject[];
extern char igPluginRepositoryList_GetVTable[];
extern char thunk_igPluginRepositoryList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igPluginRepositoryList_callbackList[];
extern char igPluginRepositoryList_className[];
extern char g_igPluginRepositoryList_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igPluginRepositoryList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igPluginRepositoryList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igPluginRepositoryList_GetMetaObject,
        igPluginRepositoryList_className,
        0x14, /* instance size */
        igPluginRepositoryList_GetVTable,
        0,
        0, /* extra callback item */
        g_igPluginRepositoryList_callbackList /* callback list */
    );
}
