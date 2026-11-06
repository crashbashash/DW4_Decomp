extern char igObjectList_GetPublishedMetaObject[];
extern char igSkinList_GetVTable[];
extern char thunk_igSkinList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igSkinList_callbackList[];
extern char igSkinList_className[];
extern char g_igSkinList_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igSkinList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igSkinList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igSkinList_GetMetaObject,
        igSkinList_className,
        0x14, /* instance size */
        igSkinList_GetVTable,
        0,
        0, /* extra callback item */
        g_igSkinList_callbackList /* callback list */
    );
}
