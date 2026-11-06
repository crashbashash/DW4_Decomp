extern char igObjectList_GetPublishedMetaObject[];
extern char igNodeListList_GetVTable[];
extern char thunk_igNodeListList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igNodeListList_callbackList[];
extern char igNodeListList_className[];
extern char g_igNodeListList_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igNodeListList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igNodeListList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igNodeListList_GetMetaObject,
        igNodeListList_className,
        0x14, /* instance size */
        igNodeListList_GetVTable,
        0,
        0, /* extra callback item */
        g_igNodeListList_callbackList /* callback list */
    );
}
