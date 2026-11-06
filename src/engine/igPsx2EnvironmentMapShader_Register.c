extern char igEnvironmentMapShader2_Register[];
extern char thunk_igPsx2EnvironmentMapShader_GetMetaObject[];
extern char igPsx2EnvironmentMapShader_GetVTable[];
extern char igEnvironmentMapShader2_GetPublishedMetaObject[];
extern char g_igPsx2EnvironmentMapShader_callbackList[];
extern char igPsx2EnvironmentMapShader_className[];
extern char g_igPsx2EnvironmentMapShader_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igPsx2EnvironmentMapShader_InitFields();

void igPsx2EnvironmentMapShader_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igPsx2EnvironmentMapShader_metaObject,
        igEnvironmentMapShader2_Register,
        igEnvironmentMapShader2_GetPublishedMetaObject,
        thunk_igPsx2EnvironmentMapShader_GetMetaObject,
        igPsx2EnvironmentMapShader_className,
        0x7C, /* instance size */
        igPsx2EnvironmentMapShader_GetVTable,
        &igPsx2EnvironmentMapShader_InitFields,
        0, /* extra callback item */
        g_igPsx2EnvironmentMapShader_callbackList /* callback list */
    );
}
