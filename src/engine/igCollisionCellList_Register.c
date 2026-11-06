extern char igObjectList_GetPublishedMetaObject[];
extern char igCollisionCellList_GetVTable[];
extern char thunk_igCollisionCellList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igCollisionCellList_callbackList[];
extern char igCollisionCellList_className[];
extern char g_igCollisionCellList_metaObject[];
int CollisionLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igCollisionCellList_Register(void) {
    CollisionLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igCollisionCellList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igCollisionCellList_GetMetaObject,
        igCollisionCellList_className,
        0x14, /* instance size */
        igCollisionCellList_GetVTable,
        0,
        0, /* extra callback item */
        g_igCollisionCellList_callbackList /* callback list */
    );
}
