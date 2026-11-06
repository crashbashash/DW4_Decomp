extern char igObjectList_GetPublishedMetaObject[];
extern char igCollisionGroupList_GetVTable[];
extern char thunk_igCollisionGroupList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igCollisionGroupList_callbackList[];
extern char igCollisionGroupList_className[];
extern char g_igCollisionGroupList_metaObject[];
int CollisionLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igCollisionGroupList_Register(void) {
    CollisionLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igCollisionGroupList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igCollisionGroupList_GetMetaObject,
        igCollisionGroupList_className,
        0x14, /* instance size */
        igCollisionGroupList_GetVTable,
        0,
        0, /* extra callback item */
        g_igCollisionGroupList_callbackList /* callback list */
    );
}
