extern char igTraversal_Register[];
extern char igTraversal_GetPublishedMetaObject[];
extern char igCommonTraversal_GetVTable[];
extern char thunk_igCommonTraversal_GetMetaObject[];
extern char g_igCommonTraversal_callbackList[];
extern char igCommonTraversal_className[];
extern char g_igCommonTraversal_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igCommonTraversal_InitFields();
int FUN_001a44d0();

void igCommonTraversal_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igCommonTraversal_metaObject,
        igTraversal_Register,
        igTraversal_GetPublishedMetaObject,
        thunk_igCommonTraversal_GetMetaObject,
        igCommonTraversal_className,
        0x1D8, /* instance size */
        igCommonTraversal_GetVTable,
        &igCommonTraversal_InitFields,
        &FUN_001a44d0, /* extra callback item */
        g_igCommonTraversal_callbackList /* callback list */
    );
}
