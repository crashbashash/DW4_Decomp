extern char igNode_Register[];
extern char igNode_GetPublishedMetaObject[];
extern char igCamera_GetVTable[];
extern char thunk_igCamera_GetMetaObject[];
extern char igCamera_className[];
extern char g_igCamera_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igCamera_InitFields();

void igCamera_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igCamera_metaObject,
        igNode_Register,
        igNode_GetPublishedMetaObject,
        thunk_igCamera_GetMetaObject,
        igCamera_className,
        0x38, /* instance size */
        igCamera_GetVTable,
        &igCamera_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
