extern char igOptBase_GetPublishedMetaObject[];
extern char igOptBase_Register[];
extern char igCreateCollisionDatabase_GetVTable[];
extern char thunk_igCreateCollisionDatabase_GetMetaObject[];
extern char g_igCreateCollisionDatabase_callbackList[];
extern char igCreateCollisionDatabase_className[];
extern char g_igCreateCollisionDatabase_metaObject[];
int CollisionLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igCreateCollisionDatabase_InitFields();

void igCreateCollisionDatabase_Register(void) {
    CollisionLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igCreateCollisionDatabase_metaObject,
        igOptBase_Register,
        igOptBase_GetPublishedMetaObject,
        thunk_igCreateCollisionDatabase_GetMetaObject,
        igCreateCollisionDatabase_className,
        0x44, /* instance size */
        igCreateCollisionDatabase_GetVTable,
        &igCreateCollisionDatabase_InitFields,
        0, /* extra callback item */
        g_igCreateCollisionDatabase_callbackList /* callback list */
    );
}
