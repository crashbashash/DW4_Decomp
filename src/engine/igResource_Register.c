extern char igObject_GetMetaObject_ParentAccessor[];
extern char igResource_GetVTable[];
extern char thunk_igResource_GetMetaObject[];
extern char igObject_Register[];
extern char g_igResource_callbackList[];
extern char igResource_className[];
extern char g_igResource_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igResource_InitFields();

void igResource_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igResource_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igResource_GetMetaObject,
        igResource_className,
        0x4C, /* instance size */
        igResource_GetVTable,
        &igResource_InitFields,
        0, /* extra callback item */
        g_igResource_callbackList /* callback list */
    );
}
