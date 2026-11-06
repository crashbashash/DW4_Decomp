extern char igGroup_GetPublishedMetaObject[];
extern char igLod_GetVTable[];
extern char thunk_igLod_GetMetaObject[];
extern char igGroup_Register[];
extern char g_igLod_callbackList[];
extern char igLod_className[];
extern char g_igLod_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igLod_InitFields();

void igLod_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igLod_metaObject,
        igGroup_Register,
        igGroup_GetPublishedMetaObject,
        thunk_igLod_GetMetaObject,
        igLod_className,
        0x44, /* instance size */
        igLod_GetVTable,
        &igLod_InitFields,
        0, /* extra callback item */
        g_igLod_callbackList /* callback list */
    );
}
