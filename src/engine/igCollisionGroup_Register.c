extern char igGroup_GetPublishedMetaObject[];
extern char igGroup_Register[];
extern char igCollisionGroup_GetVTable[];
extern char thunk_igCollisionGroup_GetMetaObject[];
extern char g_igCollisionGroup_callbackList[];
extern char igCollisionGroup_className[];
extern char g_igCollisionGroup_metaObject[];
int CollisionLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igCollisionGroup_InitFields();

void igCollisionGroup_Register(void) {
    CollisionLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igCollisionGroup_metaObject,
        igGroup_Register,
        igGroup_GetPublishedMetaObject,
        thunk_igCollisionGroup_GetMetaObject,
        igCollisionGroup_className,
        0x60, /* instance size */
        igCollisionGroup_GetVTable,
        &igCollisionGroup_InitFields,
        0, /* extra callback item */
        g_igCollisionGroup_callbackList /* callback list */
    );
}
