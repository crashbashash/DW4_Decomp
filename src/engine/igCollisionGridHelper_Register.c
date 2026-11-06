extern char igObject_GetMetaObject_ParentAccessor[];
extern char igCollisionGridHelper_GetVTable[];
extern char thunk_igCollisionGridHelper_GetMetaObject[];
extern char igObject_Register[];
extern char g_igCollisionGridHelper_callbackList[];
extern char igCollisionGridHelper_className[];
extern char g_igCollisionGridHelper_metaObject[];
int CollisionLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igCollisionGridHelper_InitFields();

void igCollisionGridHelper_Register(void) {
    CollisionLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igCollisionGridHelper_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igCollisionGridHelper_GetMetaObject,
        igCollisionGridHelper_className,
        0x10, /* instance size */
        igCollisionGridHelper_GetVTable,
        &igCollisionGridHelper_InitFields,
        0, /* extra callback item */
        g_igCollisionGridHelper_callbackList /* callback list */
    );
}
