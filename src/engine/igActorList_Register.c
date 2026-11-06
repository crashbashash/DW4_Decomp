extern char igObjectList_GetPublishedMetaObject[];
extern char igActorList_GetVTable[];
extern char thunk_igActorList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igActorList_callbackList[];
extern char igActorList_className[];
extern char g_igActorList_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igActorList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igActorList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igActorList_GetMetaObject,
        igActorList_className,
        0x14, /* instance size */
        igActorList_GetVTable,
        0,
        0, /* extra callback item */
        g_igActorList_callbackList /* callback list */
    );
}
