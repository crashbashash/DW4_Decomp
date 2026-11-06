extern char igObjectPool_Register[];
extern char igObjectPool_GetPublishedMetaObject[];
extern char igTimeAttrPool_GetVTable[];
extern char thunk_igTimeAttrPool_GetMetaObject[];
extern char g_igTimeAttrPool_callbackList[];
extern char igTimeAttrPool_className[];
extern char g_igTimeAttrPool_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igTimeAttrPool_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igTimeAttrPool_metaObject,
        igObjectPool_Register,
        igObjectPool_GetPublishedMetaObject,
        thunk_igTimeAttrPool_GetMetaObject,
        igTimeAttrPool_className,
        0x20, /* instance size */
        igTimeAttrPool_GetVTable,
        0,
        0, /* extra callback item */
        g_igTimeAttrPool_callbackList /* callback list */
    );
}
