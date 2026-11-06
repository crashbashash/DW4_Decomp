extern char igObjectList_GetPublishedMetaObject[];
extern char igCompiledTransformList_GetVTable[];
extern char thunk_igCompiledTransformList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igCompiledTransformList_callbackList[];
extern char igCompiledTransformList_className[];
extern char g_igCompiledTransformList_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igCompiledTransformList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igCompiledTransformList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igCompiledTransformList_GetMetaObject,
        igCompiledTransformList_className,
        0x14, /* instance size */
        igCompiledTransformList_GetVTable,
        0,
        0, /* extra callback item */
        g_igCompiledTransformList_callbackList /* callback list */
    );
}
