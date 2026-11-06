extern char igPlanarShadowShader_GetVTable[];
extern char thunk_igPlanarShadowShader_GetMetaObject[];
extern char igAttrSet_GetPublishedMetaObject[];
extern char igAttrSet_Register[];
extern char g_igPlanarShadowShader_callbackList[];
extern char igPlanarShadowShader_className[];
extern char g_igPlanarShadowShader_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igPlanarShadowShader_InitFields();

void igPlanarShadowShader_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igPlanarShadowShader_metaObject,
        igAttrSet_Register,
        igAttrSet_GetPublishedMetaObject,
        thunk_igPlanarShadowShader_GetMetaObject,
        igPlanarShadowShader_className,
        0x70, /* instance size */
        igPlanarShadowShader_GetVTable,
        &igPlanarShadowShader_InitFields,
        0, /* extra callback item */
        g_igPlanarShadowShader_callbackList /* callback list */
    );
}
