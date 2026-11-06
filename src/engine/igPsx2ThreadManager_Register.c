extern char igThreadManager_Register[];
extern char thunk_igPsx2ThreadManager_GetMetaObject[];
extern char igPsx2ThreadManager_GetVTable[];
extern char igThreadManager_GetPublishedMetaObject[];
extern char igPsx2ThreadManager_className[];
extern char g_igPsx2ThreadManager_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
extern int igPsx2ThreadManager_InitFields_002cf3f0[4];
void igPsx2ThreadManager_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igPsx2ThreadManager_metaObject,
        igThreadManager_Register,
        igThreadManager_GetPublishedMetaObject,
        thunk_igPsx2ThreadManager_GetMetaObject,
        igPsx2ThreadManager_className,
        0x10, /* instance size */
        igPsx2ThreadManager_GetVTable,
        &igPsx2ThreadManager_InitFields_002cf3f0[0],     /* Field adder. */
        0,                                               /* extra callback-vector item (none) */
        0                                                /* zero-terminated callback-vector item list (none) */
    );
}
