extern char igTransientShaderData_GetVTable[];
extern char thunk_igTransientShaderData_GetMetaObject[];
extern char igShaderData_GetPublishedMetaObject[];
extern char igShaderData_Register[];
extern char g_igTransientShaderData_callbackList[];
extern char igTransientShaderData_className[];
extern char g_igTransientShaderData_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igTransientShaderData_InitFields();

void igTransientShaderData_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igTransientShaderData_metaObject,
        igShaderData_Register,
        igShaderData_GetPublishedMetaObject,
        thunk_igTransientShaderData_GetMetaObject,
        igTransientShaderData_className,
        0x18, /* instance size */
        igTransientShaderData_GetVTable,
        &igTransientShaderData_InitFields,
        0, /* extra callback item */
        g_igTransientShaderData_callbackList /* callback list */
    );
}
