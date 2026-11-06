extern char igObjectPool_Register[];
extern char igObjectPool_GetPublishedMetaObject[];
extern char igProjectionMatrixAttrPool_GetVTable[];
extern char thunk_igProjectionMatrixAttrPool_GetMetaObject[];
extern char g_igProjectionMatrixAttrPool_callbackList[];
extern char igProjectionMatrixAttrPool_className[];
extern char g_igProjectionMatrixAttrPool_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igProjectionMatrixAttrPool_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igProjectionMatrixAttrPool_metaObject,
        igObjectPool_Register,
        igObjectPool_GetPublishedMetaObject,
        thunk_igProjectionMatrixAttrPool_GetMetaObject,
        igProjectionMatrixAttrPool_className,
        0x20, /* instance size */
        igProjectionMatrixAttrPool_GetVTable,
        0,
        0, /* extra callback item */
        g_igProjectionMatrixAttrPool_callbackList /* callback list */
    );
}
