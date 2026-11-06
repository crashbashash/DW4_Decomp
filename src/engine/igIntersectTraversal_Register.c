extern char igTraversal_Register[];
extern char igIntersectTraversal_GetVTable[];
extern char thunk_igIntersectTraversal_GetMetaObject[];
extern char igTraversal_GetPublishedMetaObject[];
extern char g_igIntersectTraversal_callbackList[];
extern char igIntersectTraversal_className[];
extern char g_igIntersectTraversal_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igIntersectTraversal_InitFields();
int FUN_0019e640();

void igIntersectTraversal_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igIntersectTraversal_metaObject,
        igTraversal_Register,
        igTraversal_GetPublishedMetaObject,
        thunk_igIntersectTraversal_GetMetaObject,
        igIntersectTraversal_className,
        0x40, /* instance size */
        igIntersectTraversal_GetVTable,
        &igIntersectTraversal_InitFields,
        &FUN_0019e640, /* extra callback item */
        g_igIntersectTraversal_callbackList /* callback list */
    );
}
