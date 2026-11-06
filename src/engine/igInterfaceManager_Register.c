extern char igObject_GetMetaObject_ParentAccessor[];
extern char thunk_igInterfaceManager_GetMetaObject[];
extern char igObject_Register[];
extern char g_igInterfaceManager_callbackList[];
extern char igInterfaceManager_className[];
extern char g_igInterfaceManager_metaObject[];
int WindowInputLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igInterfaceManager_InitFields();

void igInterfaceManager_Register(void) {
    WindowInputLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igInterfaceManager_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igInterfaceManager_GetMetaObject,
        igInterfaceManager_className,
        0xC, /* instance size */
        0,
        &igInterfaceManager_InitFields,
        0, /* extra callback item */
        g_igInterfaceManager_callbackList /* callback list */
    );
}
