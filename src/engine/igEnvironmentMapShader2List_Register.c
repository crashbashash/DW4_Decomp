extern char igObjectList_GetPublishedMetaObject[];
extern char igEnvironmentMapShader2List_GetVTable[];
extern char thunk_igEnvironmentMapShader2List_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igEnvironmentMapShader2List_callbackList[];
extern char igEnvironmentMapShader2List_className[];
extern char g_igEnvironmentMapShader2List_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igEnvironmentMapShader2List_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igEnvironmentMapShader2List_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igEnvironmentMapShader2List_GetMetaObject,
        igEnvironmentMapShader2List_className,
        0x14, /* instance size */
        igEnvironmentMapShader2List_GetVTable,
        0,
        0, /* extra callback item */
        g_igEnvironmentMapShader2List_callbackList /* callback list */
    );
}
