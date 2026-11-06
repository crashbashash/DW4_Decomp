extern char igObject_GetMetaObject_ParentAccessor[];
extern char igObject_Register[];
extern char igFieldSynchronizer_GetVTable[];
extern char thunk_igFieldSynchronizer_GetMetaObject[];
extern char g_igFieldSynchronizer_callbackList[];
extern char igFieldSynchronizer_className[];
extern char g_igFieldSynchronizer_metaObject[];
int igMetaObject_RegisterClass();
int GuiLibrary_MarkRegistered();
int igFieldSynchronizer_InitFields();

void igFieldSynchronizer_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igFieldSynchronizer_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igFieldSynchronizer_GetMetaObject,
        igFieldSynchronizer_className,
        0xC, /* instance size */
        igFieldSynchronizer_GetVTable,
        &igFieldSynchronizer_InitFields,
        0, /* extra callback item */
        g_igFieldSynchronizer_callbackList /* callback list */
    );
}
