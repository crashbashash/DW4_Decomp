extern char igObject_GetMetaObject_ParentAccessor[];
extern char igSorter_GetVTable[];
extern char thunk_igSorter_GetMetaObject[];
extern char igObject_Register[];
extern char g_igSorter_callbackList[];
extern char igSorter_className[];
extern char g_igSorter_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igSorter_InitFields();

void igSorter_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igSorter_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igSorter_GetMetaObject,
        igSorter_className,
        0x84, /* instance size */
        igSorter_GetVTable,
        &igSorter_InitFields,
        0, /* extra callback item */
        g_igSorter_callbackList /* callback list */
    );
}
