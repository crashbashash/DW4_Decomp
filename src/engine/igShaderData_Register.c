extern char igObject_GetMetaObject_ParentAccessor[];
extern char igShaderData_GetVTable[];
extern char thunk_igShaderData_GetMetaObject[];
extern char igObject_Register[];
extern char g_igShaderData_callbackList[];
extern char igShaderData_className[];
extern char g_igShaderData_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igShaderData_InitFields();

void igShaderData_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igShaderData_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igShaderData_GetMetaObject,
        igShaderData_className,
        0x18, /* instance size */
        igShaderData_GetVTable,
        &igShaderData_InitFields,
        0, /* extra callback item */
        g_igShaderData_callbackList /* callback list */
    );
}
