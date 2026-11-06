extern char igObject_GetMetaObject_ParentAccessor[];
extern char igRenderPackage_GetVTable[];
extern char thunk_igRenderPackage_GetMetaObject[];
extern char igObject_Register[];
extern char g_igRenderPackage_callbackList[];
extern char igRenderPackage_className[];
extern char g_igRenderPackage_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igRenderPackage_InitFields();

void igRenderPackage_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igRenderPackage_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igRenderPackage_GetMetaObject,
        igRenderPackage_className,
        0x20, /* instance size */
        igRenderPackage_GetVTable,
        &igRenderPackage_InitFields,
        0, /* extra callback item */
        g_igRenderPackage_callbackList /* callback list */
    );
}
