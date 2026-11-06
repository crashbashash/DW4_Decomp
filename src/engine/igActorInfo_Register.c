extern char igInfo_GetPublishedMetaObject[];
extern char igActorInfo_GetVTable[];
extern char thunk_igActorInfo_GetMetaObject[];
extern char igInfo_Register[];
extern char g_igActorInfo_callbackList[];
extern char igActorInfo_className[];
extern char g_igActorInfo_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igActorInfo_InitFields();

void igActorInfo_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igActorInfo_metaObject,
        igInfo_Register,
        igInfo_GetPublishedMetaObject,
        thunk_igActorInfo_GetMetaObject,
        igActorInfo_className,
        0x28, /* instance size */
        igActorInfo_GetVTable,
        &igActorInfo_InitFields,
        0, /* extra callback item */
        g_igActorInfo_callbackList /* callback list */
    );
}
