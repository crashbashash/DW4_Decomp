extern char igObjectList_GetPublishedMetaObject[];
extern char igObjectPool_GetVTable[];
extern char thunk_igObjectPool_GetMetaObject[];
extern char igObjectList_Register[];
extern char igObjectPool_className[];
extern char g_igObjectPool_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igObjectPool_InitFields();

void igObjectPool_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igObjectPool_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igObjectPool_GetMetaObject,
        igObjectPool_className,
        0x20, /* instance size */
        igObjectPool_GetVTable,
        &igObjectPool_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
