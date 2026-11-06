extern char igObject_GetMetaObject_ParentAccessor[];
extern char igPluginHelper_GetVTable[];
extern char thunk_igPluginHelper_GetMetaObject[];
extern char igObject_Register[];
extern char g_igPluginHelper_callbackList[];
extern char igPluginHelper_className[];
extern char g_igPluginHelper_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igPluginHelper_InitFields();

void igPluginHelper_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igPluginHelper_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igPluginHelper_GetMetaObject,
        igPluginHelper_className,
        0x18, /* instance size */
        igPluginHelper_GetVTable,
        &igPluginHelper_InitFields,
        0, /* extra callback item */
        g_igPluginHelper_callbackList /* callback list */
    );
}
