extern char igObject_GetMetaObject_ParentAccessor[];
extern char thunk_igContext_GetMetaObject[];
extern char igObject_Register[];
extern char g_igContext_callbackList[];
extern char igContext_className[];
extern char g_igContext_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igContext_InitFields();

void igContext_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igContext_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igContext_GetMetaObject,
        igContext_className,
        0x14, /* instance size */
        0,
        &igContext_InitFields,
        0, /* extra callback item */
        g_igContext_callbackList /* callback list */
    );
}
