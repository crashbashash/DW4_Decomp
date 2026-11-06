extern char igObjectPool_Register[];
extern char igObjectPool_GetPublishedMetaObject[];
extern char igLightStateAttrPool_GetVTable[];
extern char thunk_igLightStateAttrPool_GetMetaObject[];
extern char g_igLightStateAttrPool_callbackList[];
extern char igLightStateAttrPool_className[];
extern char g_igLightStateAttrPool_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igLightStateAttrPool_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igLightStateAttrPool_metaObject,
        igObjectPool_Register,
        igObjectPool_GetPublishedMetaObject,
        thunk_igLightStateAttrPool_GetMetaObject,
        igLightStateAttrPool_className,
        0x20, /* instance size */
        igLightStateAttrPool_GetVTable,
        0,
        0, /* extra callback item */
        g_igLightStateAttrPool_callbackList /* callback list */
    );
}
