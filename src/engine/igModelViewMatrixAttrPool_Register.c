extern char igObjectPool_Register[];
extern char igObjectPool_GetPublishedMetaObject[];
extern char igModelViewMatrixAttrPool_GetVTable[];
extern char thunk_igModelViewMatrixAttrPool_GetMetaObject[];
extern char g_igModelViewMatrixAttrPool_callbackList[];
extern char igModelViewMatrixAttrPool_className[];
extern char g_igModelViewMatrixAttrPool_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igModelViewMatrixAttrPool_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igModelViewMatrixAttrPool_metaObject,
        igObjectPool_Register,
        igObjectPool_GetPublishedMetaObject,
        thunk_igModelViewMatrixAttrPool_GetMetaObject,
        igModelViewMatrixAttrPool_className,
        0x20, /* instance size */
        igModelViewMatrixAttrPool_GetVTable,
        0,
        0, /* extra callback item */
        g_igModelViewMatrixAttrPool_callbackList /* callback list */
    );
}
