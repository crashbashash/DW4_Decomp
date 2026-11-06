extern char igObjectList_GetPublishedMetaObject[];
extern char igTransformList_GetVTable[];
extern char thunk_igTransformList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igTransformList_callbackList[];
extern char igTransformList_className[];
extern char g_igTransformList_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igTransformList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igTransformList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igTransformList_GetMetaObject,
        igTransformList_className,
        0x14, /* instance size */
        igTransformList_GetVTable,
        0,
        0, /* extra callback item */
        g_igTransformList_callbackList /* callback list */
    );
}
