extern char igObject_GetMetaObject_ParentAccessor[];
extern char thunk_igInterfaced_GetMetaObject[];
extern char igObject_Register[];
extern char g_igInterfaced_callbackList[];
extern char igInterfaced_className[];
extern char g_igInterfaced_metaObject[];
int BaseLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igInterfaced_InitFields();

void igInterfaced_Register(void) {
    BaseLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igInterfaced_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igInterfaced_GetMetaObject,
        igInterfaced_className,
        0x20, /* instance size */
        0,
        &igInterfaced_InitFields,
        0, /* extra callback item */
        g_igInterfaced_callbackList /* callback list */
    );
}
