extern char igDataList_GetPublishedMetaObject[];
extern char igTraversalFunctionList_GetVTable[];
extern char thunk_igTraversalFunctionList_GetMetaObject[];
extern char igDataList_Register[];
extern char igTraversalFunctionList_className[];
extern char g_igTraversalFunctionList_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igTraversalFunctionList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igTraversalFunctionList_metaObject,
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igTraversalFunctionList_GetMetaObject,
        igTraversalFunctionList_className,
        0x14, /* instance size */
        igTraversalFunctionList_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
