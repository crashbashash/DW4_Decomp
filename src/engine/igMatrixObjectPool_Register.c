extern char igObjectPool_Register[];
extern char igObjectPool_GetPublishedMetaObject[];
extern char igMatrixObjectPool_GetVTable[];
extern char thunk_igMatrixObjectPool_GetMetaObject[];
extern char g_igMatrixObjectPool_callbackList[];
extern char igMatrixObjectPool_className[];
extern char g_igMatrixObjectPool_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igMatrixObjectPool_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMatrixObjectPool_metaObject,
        igObjectPool_Register,
        igObjectPool_GetPublishedMetaObject,
        thunk_igMatrixObjectPool_GetMetaObject,
        igMatrixObjectPool_className,
        0x20, /* instance size */
        igMatrixObjectPool_GetVTable,
        0,
        0, /* extra callback item */
        g_igMatrixObjectPool_callbackList /* callback list */
    );
}
