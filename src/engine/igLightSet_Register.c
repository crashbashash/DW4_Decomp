extern char igNode_Register[];
extern char igLightSet_GetVTable[];
extern char thunk_igLightSet_GetMetaObject[];
extern char igNode_GetPublishedMetaObject[];
extern char g_igLightSet_callbackList[];
extern char igLightSet_className[];
extern char g_igLightSet_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igLightSet_InitFields();

void igLightSet_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igLightSet_metaObject,
        igNode_Register,
        igNode_GetPublishedMetaObject,
        thunk_igLightSet_GetMetaObject,
        igLightSet_className,
        0x20, /* instance size */
        igLightSet_GetVTable,
        &igLightSet_InitFields,
        0, /* extra callback item */
        g_igLightSet_callbackList /* callback list */
    );
}
