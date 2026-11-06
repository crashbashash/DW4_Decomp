extern char igNamedObject_GetPublishedMetaObject[];
extern char igSearchSceneGraph_GetVTable[];
extern char thunk_igSearchSceneGraph_GetMetaObject[];
extern char igNamedObject_Register[];
extern char g_igSearchSceneGraph_callbackList[];
extern char igSearchSceneGraph_className[];
extern char g_igSearchSceneGraph_metaObject[];
int SceneSearchLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igSearchSceneGraph_InitFields();

void igSearchSceneGraph_Register(void) {
    SceneSearchLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igSearchSceneGraph_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        thunk_igSearchSceneGraph_GetMetaObject,
        igSearchSceneGraph_className,
        0x1C, /* instance size */
        igSearchSceneGraph_GetVTable,
        &igSearchSceneGraph_InitFields,
        0, /* extra callback item */
        g_igSearchSceneGraph_callbackList /* callback list */
    );
}
