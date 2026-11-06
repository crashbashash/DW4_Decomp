extern char igInterface_GetPublishedMetaObject[];
extern char igLockInterface_GetVTable[];
extern char thunk_igLockInterface_GetMetaObject[];
extern char igInterface_Register[];
extern char g_igLockInterface_callbackList[];
extern char igLockInterface_className[];
extern char g_igLockInterface_metaObject[];
int BaseLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igLockInterface_InitFields();

void igLockInterface_Register(void) {
    BaseLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igLockInterface_metaObject,
        igInterface_Register,
        igInterface_GetPublishedMetaObject,
        thunk_igLockInterface_GetMetaObject,
        igLockInterface_className,
        0x2C, /* instance size */
        igLockInterface_GetVTable,
        &igLockInterface_InitFields,
        0, /* extra callback item */
        g_igLockInterface_callbackList /* callback list */
    );
}
