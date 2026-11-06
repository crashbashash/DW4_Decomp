extern char igObject_GetMetaObject_ParentAccessor[];
extern char igShaderProcessor_GetVTable[];
extern char thunk_igShaderProcessor_GetMetaObject[];
extern char igObject_Register[];
extern char igShaderProcessor_className[];
extern char g_igShaderProcessor_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igShaderProcessor_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igShaderProcessor_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igShaderProcessor_GetMetaObject,
        igShaderProcessor_className,
        8, /* instance size */
        igShaderProcessor_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
