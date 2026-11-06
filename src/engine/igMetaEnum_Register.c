extern char igObject_GetMetaObject_ParentAccessor[];
extern char igMetaEnum_GetVTable[];
extern char thunk_igMetaEnum_GetMetaObject[];
extern char igObject_Register[];
extern char g_igMetaEnum_callbackList[];
extern char igMetaEnum_className[];
extern char g_igMetaEnum_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igMetaEnum_InitFields();

void igMetaEnum_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMetaEnum_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igMetaEnum_GetMetaObject,
        igMetaEnum_className,
        0x14, /* instance size */
        igMetaEnum_GetVTable,
        &igMetaEnum_InitFields,
        0, /* extra callback item */
        g_igMetaEnum_callbackList /* callback list */
    );
}
