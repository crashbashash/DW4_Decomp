extern char igInfo_GetPublishedMetaObject[];
extern char igCollisionInfo_GetVTable[];
extern char thunk_igCollisionInfo_GetMetaObject[];
extern char igInfo_Register[];
extern char g_igCollisionInfo_callbackList[];
extern char igCollisionInfo_className[];
extern char g_igCollisionInfo_metaObject[];
int CollisionLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igCollisionInfo_InitFields();

void igCollisionInfo_Register(void) {
    CollisionLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igCollisionInfo_metaObject,
        igInfo_Register,
        igInfo_GetPublishedMetaObject,
        thunk_igCollisionInfo_GetMetaObject,
        igCollisionInfo_className,
        0x18, /* instance size */
        igCollisionInfo_GetVTable,
        &igCollisionInfo_InitFields,
        0, /* extra callback item */
        g_igCollisionInfo_callbackList /* callback list */
    );
}
