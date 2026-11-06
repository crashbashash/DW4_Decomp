extern char igInterfaced_GetPublishedMetaObject[];
extern char thunk_igLockBase_GetMetaObject[];
extern char igInterfaced_Register[];
extern char igLockBase_className[];
extern char g_igLockBase_metaObject[];
int BaseLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igLockBase_Register(void) {
    BaseLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igLockBase_metaObject,
        igInterfaced_Register,
        igInterfaced_GetPublishedMetaObject,
        thunk_igLockBase_GetMetaObject,
        igLockBase_className,
        0x20, /* instance size */
        0,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
