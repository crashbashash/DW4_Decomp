extern char igObject_GetMetaObject_ParentAccessor[];
extern char igProbe_GetVTable[];
extern char thunk_igProbe_GetMetaObject[];
extern char igObject_Register[];
extern char g_igProbe_callbackList[];
extern char igProbe_className[];
extern char g_igProbe_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igProbe_InitFields();

void igProbe_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igProbe_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igProbe_GetMetaObject,
        igProbe_className,
        0x14, /* instance size */
        igProbe_GetVTable,
        &igProbe_InitFields,
        0, /* extra callback item */
        g_igProbe_callbackList /* callback list */
    );
}
