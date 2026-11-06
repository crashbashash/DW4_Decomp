extern char igObject_GetMetaObject_ParentAccessor[];
extern char igMessenger_GetVTable[];
extern char thunk_igMessenger_GetMetaObject[];
extern char igObject_Register[];
extern char g_igMessenger_callbackList[];
extern char igMessenger_className[];
extern char g_igMessenger_metaObject[];
int InsightLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igMessenger_InitFields();

void igMessenger_Register(void) {
    InsightLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMessenger_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igMessenger_GetMetaObject,
        igMessenger_className,
        0xC, /* instance size */
        igMessenger_GetVTable,
        &igMessenger_InitFields,
        0, /* extra callback item */
        g_igMessenger_callbackList /* callback list */
    );
}
