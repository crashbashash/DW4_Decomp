extern char igObject_GetMetaObject_ParentAccessor[];
extern char igObject_Register[];
extern char igHotKeyBinding_GetVTable[];
extern char thunk_igHotKeyBinding_GetMetaObject[];
extern char g_igHotKeyBinding_callbackList[];
extern char igHotKeyBinding_className[];
extern char g_igHotKeyBinding_metaObject[];
int igMetaObject_RegisterClass();
int GuiLibrary_MarkRegistered();
int igHotKeyBinding_InitFields();

void igHotKeyBinding_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igHotKeyBinding_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igHotKeyBinding_GetMetaObject,
        igHotKeyBinding_className,
        0x14, /* instance size */
        igHotKeyBinding_GetVTable,
        &igHotKeyBinding_InitFields,
        0, /* extra callback item */
        g_igHotKeyBinding_callbackList /* callback list */
    );
}
