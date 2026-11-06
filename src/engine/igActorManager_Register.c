extern char igInfoManager_GetPublishedMetaObject[];
extern char igInfoManager_Register[];
extern char igActorManager_GetVTable[];
extern char thunk_igActorManager_GetMetaObject[];
extern char g_igActorManager_callbackList[];
extern char igActorManager_className[];
extern char g_igActorManager_metaObject[];
int igMetaObject_RegisterClass();
int ViewerLibrary_MarkRegistered();
int igActorManager_InitFields();

void igActorManager_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igActorManager_metaObject,
        igInfoManager_Register,
        igInfoManager_GetPublishedMetaObject,
        thunk_igActorManager_GetMetaObject,
        igActorManager_className,
        0x38, /* instance size */
        igActorManager_GetVTable,
        &igActorManager_InitFields,
        0, /* extra callback item */
        g_igActorManager_callbackList /* callback list */
    );
}
