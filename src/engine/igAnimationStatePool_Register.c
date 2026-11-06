extern char igObjectPool_Register[];
extern char igObjectPool_GetPublishedMetaObject[];
extern char igAnimationStatePool_GetVTable[];
extern char thunk_igAnimationStatePool_GetMetaObject[];
extern char g_igAnimationStatePool_callbackList[];
extern char igAnimationStatePool_className[];
extern char g_igAnimationStatePool_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igAnimationStatePool_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igAnimationStatePool_metaObject,
        igObjectPool_Register,
        igObjectPool_GetPublishedMetaObject,
        thunk_igAnimationStatePool_GetMetaObject,
        igAnimationStatePool_className,
        0x20, /* instance size */
        igAnimationStatePool_GetVTable,
        0,
        0, /* extra callback item */
        g_igAnimationStatePool_callbackList /* callback list */
    );
}
