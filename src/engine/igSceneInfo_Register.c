extern char igInfo_GetPublishedMetaObject[];
extern char igSceneInfo_GetVTable[];
extern char thunk_igSceneInfo_GetMetaObject[];
extern char igInfo_Register[];
extern char g_igSceneInfo_callbackList[];
extern char igSceneInfo_className[];
extern char g_igSceneInfo_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igSceneInfo_InitFields();

void igSceneInfo_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igSceneInfo_metaObject,
        igInfo_Register,
        igInfo_GetPublishedMetaObject,
        thunk_igSceneInfo_GetMetaObject,
        igSceneInfo_className,
        0x40, /* instance size */
        igSceneInfo_GetVTable,
        &igSceneInfo_InitFields,
        0, /* extra callback item */
        g_igSceneInfo_callbackList /* callback list */
    );
}
