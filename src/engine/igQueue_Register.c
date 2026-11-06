extern char igObject_GetMetaObject_ParentAccessor[];
extern char thunk_igQueue_GetMetaObject[];
extern char igObject_Register[];
extern char g_igQueue_callbackList[];
extern char igQueue_className[];
extern char g_igQueue_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igQueue_InitFields();

void igQueue_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igQueue_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igQueue_GetMetaObject,
        igQueue_className,
        0xC, /* instance size */
        0,
        &igQueue_InitFields,
        0, /* extra callback item */
        g_igQueue_callbackList /* callback list */
    );
}
