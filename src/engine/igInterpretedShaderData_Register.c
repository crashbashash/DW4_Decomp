extern char igTransientShaderData_Register[];
extern char igInterpretedShaderData_GetVTable[];
extern char thunk_igInterpretedShaderData_GetMetaObject[];
extern char igTransientShaderData_GetPublishedMetaObject[];
extern char g_igInterpretedShaderData_callbackList[];
extern char igInterpretedShaderData_className[];
extern char g_igInterpretedShaderData_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igInterpretedShaderData_InitFields();

void igInterpretedShaderData_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igInterpretedShaderData_metaObject,
        igTransientShaderData_Register,
        igTransientShaderData_GetPublishedMetaObject,
        thunk_igInterpretedShaderData_GetMetaObject,
        igInterpretedShaderData_className,
        0x20, /* instance size */
        igInterpretedShaderData_GetVTable,
        &igInterpretedShaderData_InitFields,
        0, /* extra callback item */
        g_igInterpretedShaderData_callbackList /* callback list */
    );
}
