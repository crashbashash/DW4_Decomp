extern char igObject_GetMetaObject_ParentAccessor[];
extern char igRegistry_GetVTable[];
extern char thunk_igRegistry_GetMetaObject[];
extern char igObject_Register[];
extern char g_igRegistry_callbackList[];
extern char igRegistry_className[];
extern char g_igRegistry_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igRegistry_InitFields();

void igRegistry_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igRegistry_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igRegistry_GetMetaObject,
        igRegistry_className,
        0x18, /* instance size */
        igRegistry_GetVTable,
        &igRegistry_InitFields,
        0, /* extra callback item */
        g_igRegistry_callbackList /* callback list */
    );
}
