extern char igGroup_GetPublishedMetaObject[];
extern char igGroup_Register[];
extern char igActor_GetVTable[];
extern char thunk_igActor_GetMetaObject[];
extern char g_igActor_callbackList[];
extern char igActor_className[];
extern char g_igActor_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igActor_InitFields();

void igActor_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igActor_metaObject,
        igGroup_Register,
        igGroup_GetPublishedMetaObject,
        thunk_igActor_GetMetaObject,
        igActor_className,
        0x100, /* instance size */
        igActor_GetVTable,
        &igActor_InitFields,
        0, /* extra callback item */
        g_igActor_callbackList /* callback list */
    );
}
