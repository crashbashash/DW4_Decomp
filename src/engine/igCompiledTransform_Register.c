extern char igObject_GetMetaObject_ParentAccessor[];
extern char igCompiledTransform_GetVTable[];
extern char thunk_igCompiledTransform_GetMetaObject[];
extern char igObject_Register[];
extern char g_igCompiledTransform_callbackList[];
extern char igCompiledTransform_className[];
extern char g_igCompiledTransform_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igCompiledTransform_InitFields();

void igCompiledTransform_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igCompiledTransform_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igCompiledTransform_GetMetaObject,
        igCompiledTransform_className,
        0x24, /* instance size */
        igCompiledTransform_GetVTable,
        &igCompiledTransform_InitFields,
        0, /* extra callback item */
        g_igCompiledTransform_callbackList /* callback list */
    );
}
