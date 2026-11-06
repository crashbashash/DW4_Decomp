extern char igCommonTraversal_GetPublishedMetaObject[];
extern char igCompileTraversal_GetVTable[];
extern char thunk_igCompileTraversal_GetMetaObject[];
extern char igCommonTraversal_Register[];
extern char g_igCompileTraversal_callbackList[];
extern char igCompileTraversal_className[];
extern char g_igCompileTraversal_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igCompileTraversal_InitFields();
int FUN_001a33e0();

void igCompileTraversal_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igCompileTraversal_metaObject,
        igCommonTraversal_Register,
        igCommonTraversal_GetPublishedMetaObject,
        thunk_igCompileTraversal_GetMetaObject,
        igCompileTraversal_className,
        0x208, /* instance size */
        igCompileTraversal_GetVTable,
        &igCompileTraversal_InitFields,
        &FUN_001a33e0, /* extra callback item */
        g_igCompileTraversal_callbackList /* callback list */
    );
}
