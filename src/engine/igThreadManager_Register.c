extern char igObject_GetMetaObject_ParentAccessor[];
extern char thunk_igThreadManager_GetMetaObject[];
extern char igObject_Register[];
extern char g_igThreadManager_callbackList[];
extern char igThreadManager_className[];
extern char g_igThreadManager_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
extern int thunk_FUN_0030e480[4];
int igThreadManager_InitFields();

void igThreadManager_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igThreadManager_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igThreadManager_GetMetaObject,
        igThreadManager_className,
        0x10, /* instance size */
        0,
        &igThreadManager_InitFields,
        thunk_FUN_0030e480, /* extra callback item */
        g_igThreadManager_callbackList /* callback list */
    );
}
