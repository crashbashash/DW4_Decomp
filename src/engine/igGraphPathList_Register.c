extern char igObjectList_GetPublishedMetaObject[];
extern char igGraphPathList_GetVTable[];
extern char thunk_igGraphPathList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igGraphPathList_callbackList[];
extern char igGraphPathList_className[];
extern char g_igGraphPathList_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igGraphPathList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igGraphPathList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igGraphPathList_GetMetaObject,
        igGraphPathList_className,
        0x14, /* instance size */
        igGraphPathList_GetVTable,
        0,
        0, /* extra callback item */
        g_igGraphPathList_callbackList /* callback list */
    );
}
