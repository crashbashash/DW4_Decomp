extern char igAttrSet_GetPublishedMetaObject[];
extern char igBlendMatrixSelect_GetVTable[];
extern char thunk_igBlendMatrixSelect_GetMetaObject[];
extern char igAttrSet_Register[];
extern char g_igBlendMatrixSelect_callbackList[];
extern char igBlendMatrixSelect_className[];
extern char g_igBlendMatrixSelect_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igBlendMatrixSelect_InitFields();

void igBlendMatrixSelect_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igBlendMatrixSelect_metaObject,
        igAttrSet_Register,
        igAttrSet_GetPublishedMetaObject,
        thunk_igBlendMatrixSelect_GetMetaObject,
        igBlendMatrixSelect_className,
        0xAC, /* instance size */
        igBlendMatrixSelect_GetVTable,
        &igBlendMatrixSelect_InitFields,
        0, /* extra callback item */
        g_igBlendMatrixSelect_callbackList /* callback list */
    );
}
