extern char igObject_GetMetaObject_ParentAccessor[];
extern char igEnbayaContextPool_GetVTable[];
extern char thunk_igEnbayaContextPool_GetMetaObject[];
extern char igObject_Register[];
extern char g_igEnbayaContextPool_callbackList[];
extern char igEnbayaContextPool_className[];
extern char g_igEnbayaContextPool_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igEnbayaContextPool_InitFields();

void igEnbayaContextPool_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igEnbayaContextPool_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igEnbayaContextPool_GetMetaObject,
        igEnbayaContextPool_className,
        0x14, /* instance size */
        igEnbayaContextPool_GetVTable,
        &igEnbayaContextPool_InitFields,
        0, /* extra callback item */
        g_igEnbayaContextPool_callbackList /* callback list */
    );
}
