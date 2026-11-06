extern char igNode_Register[];
extern char igNode_GetPublishedMetaObject[];
extern char igGroup_GetVTable[];
extern char thunk_igGroup_GetMetaObject[];
extern char g_igGroup_callbackList[];
extern char igGroup_className[];
extern char g_igGroup_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igGroup_InitFields();

void igGroup_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igGroup_metaObject,
        igNode_Register,
        igNode_GetPublishedMetaObject,
        thunk_igGroup_GetMetaObject,
        igGroup_className,
        0x20, /* instance size */
        igGroup_GetVTable,
        &igGroup_InitFields,
        0, /* extra callback item */
        g_igGroup_callbackList /* callback list */
    );
}
