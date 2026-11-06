extern char igObjectList_GetPublishedMetaObject[];
extern char igNodeList_GetVTable[];
extern char thunk_igNodeList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igNodeList_callbackList[];
extern char igNodeList_className[];
extern char g_igNodeList_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igNodeList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igNodeList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igNodeList_GetMetaObject,
        igNodeList_className,
        0x14, /* instance size */
        igNodeList_GetVTable,
        0,
        0, /* extra callback item */
        g_igNodeList_callbackList /* callback list */
    );
}
