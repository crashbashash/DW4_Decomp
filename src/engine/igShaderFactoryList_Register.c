extern char igObjectList_GetPublishedMetaObject[];
extern char igShaderFactoryList_GetVTable[];
extern char thunk_igShaderFactoryList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igShaderFactoryList_callbackList[];
extern char igShaderFactoryList_className[];
extern char g_igShaderFactoryList_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igShaderFactoryList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igShaderFactoryList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igShaderFactoryList_GetMetaObject,
        igShaderFactoryList_className,
        0x14, /* instance size */
        igShaderFactoryList_GetVTable,
        0,
        0, /* extra callback item */
        g_igShaderFactoryList_callbackList /* callback list */
    );
}
