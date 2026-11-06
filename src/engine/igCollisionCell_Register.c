extern char igObject_GetMetaObject_ParentAccessor[];
extern char igCollisionCell_GetVTable[];
extern char thunk_igCollisionCell_GetMetaObject[];
extern char igObject_Register[];
extern char g_igCollisionCell_callbackList[];
extern char igCollisionCell_className[];
extern char g_igCollisionCell_metaObject[];
int CollisionLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igCollisionCell_InitFields();

void igCollisionCell_Register(void) {
    CollisionLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igCollisionCell_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igCollisionCell_GetMetaObject,
        igCollisionCell_className,
        0x20, /* instance size */
        igCollisionCell_GetVTable,
        &igCollisionCell_InitFields,
        0, /* extra callback item */
        g_igCollisionCell_callbackList /* callback list */
    );
}
