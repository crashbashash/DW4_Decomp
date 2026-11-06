extern char igGroup_GetPublishedMetaObject[];
extern char igProjectiveShadowShader_GetVTable[];
extern char thunk_igProjectiveShadowShader_GetMetaObject[];
extern char igGroup_Register[];
extern char g_igProjectiveShadowShader_callbackList[];
extern char igProjectiveShadowShader_className[];
extern char g_igProjectiveShadowShader_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igProjectiveShadowShader_InitFields();

void igProjectiveShadowShader_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igProjectiveShadowShader_metaObject,
        igGroup_Register,
        igGroup_GetPublishedMetaObject,
        thunk_igProjectiveShadowShader_GetMetaObject,
        igProjectiveShadowShader_className,
        0xF0, /* instance size */
        igProjectiveShadowShader_GetVTable,
        &igProjectiveShadowShader_InitFields,
        0, /* extra callback item */
        g_igProjectiveShadowShader_callbackList /* callback list */
    );
}
