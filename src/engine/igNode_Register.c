extern char igNamedObject_GetPublishedMetaObject[];
extern char igNode_GetVTable[];
extern char thunk_igNode_GetMetaObject[];
extern char igNamedObject_Register[];
extern char g_igNode_callbackList[];
extern char igNode_className[];
extern char g_igNode_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igNode_InitFields();

void igNode_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igNode_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        thunk_igNode_GetMetaObject,
        igNode_className,
        0x1C, /* instance size */
        igNode_GetVTable,
        &igNode_InitFields,
        0, /* extra callback item */
        g_igNode_callbackList /* callback list */
    );
}
