extern char igGroup_GetPublishedMetaObject[];
extern char igGroup_Register[];
extern char thunk_igEnvironmentMapShader2_GetMetaObject[];
extern char g_igEnvironmentMapShader2_callbackList[];
extern char igEnvironmentMapShader2_className[];
extern char g_igEnvironmentMapShader2_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igEnvironmentMapShader2_InitFields();

void igEnvironmentMapShader2_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igEnvironmentMapShader2_metaObject,
        igGroup_Register,
        igGroup_GetPublishedMetaObject,
        thunk_igEnvironmentMapShader2_GetMetaObject,
        igEnvironmentMapShader2_className,
        0x70, /* instance size */
        0,
        &igEnvironmentMapShader2_InitFields,
        0, /* extra callback item */
        g_igEnvironmentMapShader2_callbackList /* callback list */
    );
}
