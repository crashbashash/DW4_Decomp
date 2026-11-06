extern char igFrustCullTraversal_GetVTable[];
extern char thunk_igFrustCullTraversal_GetMetaObject[];
extern char igCommonTraversal_GetPublishedMetaObject[];
extern char igCommonTraversal_Register[];
extern char g_igFrustCullTraversal_callbackList[];
extern char igFrustCullTraversal_className[];
extern char g_igFrustCullTraversal_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igFrustCullTraversal_InitFields();
int FUN_001a13a0();

void igFrustCullTraversal_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igFrustCullTraversal_metaObject,
        igCommonTraversal_Register,
        igCommonTraversal_GetPublishedMetaObject,
        thunk_igFrustCullTraversal_GetMetaObject,
        igFrustCullTraversal_className,
        0x230, /* instance size */
        igFrustCullTraversal_GetVTable,
        &igFrustCullTraversal_InitFields,
        &FUN_001a13a0, /* extra callback item */
        g_igFrustCullTraversal_callbackList /* callback list */
    );
}
