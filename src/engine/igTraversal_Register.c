extern char igObject_GetMetaObject_ParentAccessor[];
extern char igTraversal_GetVTable[];
extern char thunk_igTraversal_GetMetaObject[];
extern char igObject_Register[];
extern char g_igTraversal_callbackList[];
extern char igTraversal_className[];
extern char g_igTraversal_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igTraversal_InitFields();
int FUN_00194690();

void igTraversal_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igTraversal_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igTraversal_GetMetaObject,
        igTraversal_className,
        0x20, /* instance size */
        igTraversal_GetVTable,
        &igTraversal_InitFields,
        &FUN_00194690, /* extra callback item */
        g_igTraversal_callbackList /* callback list */
    );
}
