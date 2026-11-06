extern char igObject_GetMetaObject_ParentAccessor[];
extern char igCollisionGrid_GetVTable[];
extern char thunk_igCollisionGrid_GetMetaObject[];
extern char igObject_Register[];
extern char g_igCollisionGrid_callbackList[];
extern char igCollisionGrid_className[];
extern char g_igCollisionGrid_metaObject[];
int CollisionLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igCollisionGrid_InitFields();

void igCollisionGrid_Register(void) {
    CollisionLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igCollisionGrid_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igCollisionGrid_GetMetaObject,
        igCollisionGrid_className,
        0x4C, /* instance size */
        igCollisionGrid_GetVTable,
        &igCollisionGrid_InitFields,
        0, /* extra callback item */
        g_igCollisionGrid_callbackList /* callback list */
    );
}
