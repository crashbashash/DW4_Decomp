extern char igObject_GetMetaObject_ParentAccessor[];
extern char igEventTracker_GetVTable[];
extern char thunk_igEventTracker_GetMetaObject[];
extern char igObject_Register[];
extern char g_igEventTracker_callbackList[];
extern char igEventTracker_className[];
extern char g_igEventTracker_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igEventTracker_InitFields();

void igEventTracker_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igEventTracker_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igEventTracker_GetMetaObject,
        igEventTracker_className,
        0x2530, /* instance size */
        igEventTracker_GetVTable,
        &igEventTracker_InitFields,
        0, /* extra callback item */
        g_igEventTracker_callbackList /* callback list */
    );
}
