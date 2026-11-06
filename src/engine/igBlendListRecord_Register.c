extern char igObject_GetMetaObject_ParentAccessor[];
extern char igBlendListRecord_GetVTable[];
extern char thunk_igBlendListRecord_GetMetaObject[];
extern char igObject_Register[];
extern char g_igBlendListRecord_callbackList[];
extern char igBlendListRecord_className[];
extern char g_igBlendListRecord_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igBlendListRecord_InitFields();

void igBlendListRecord_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igBlendListRecord_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igBlendListRecord_GetMetaObject,
        igBlendListRecord_className,
        0x10, /* instance size */
        igBlendListRecord_GetVTable,
        &igBlendListRecord_InitFields,
        0, /* extra callback item */
        g_igBlendListRecord_callbackList /* callback list */
    );
}
