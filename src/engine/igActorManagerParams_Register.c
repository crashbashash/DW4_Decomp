extern char igModel_GetPublishedMetaObject[];
extern char igModel_Register[];
extern char igActorManagerParams_GetVTable[];
extern char thunk_igActorManagerParams_GetMetaObject[];
extern char igActorManagerParams_className[];
extern char g_igActorManagerParams_metaObject[];
int igMetaObject_RegisterClass();
int ViewerLibrary_MarkRegistered();
int igActorManagerParams_InitFields();

void igActorManagerParams_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igActorManagerParams_metaObject,
        igModel_Register,
        igModel_GetPublishedMetaObject,
        thunk_igActorManagerParams_GetMetaObject,
        igActorManagerParams_className,
        0x10, /* instance size */
        igActorManagerParams_GetVTable,
        &igActorManagerParams_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
