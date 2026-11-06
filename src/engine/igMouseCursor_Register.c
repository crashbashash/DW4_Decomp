extern char igObject_GetMetaObject_ParentAccessor[];
extern char igObject_Register[];
extern char igMouseCursor_GetVTable[];
extern char thunk_igMouseCursor_GetMetaObject[];
extern char g_igMouseCursor_callbackList[];
extern char igMouseCursor_className[];
extern char g_igMouseCursor_metaObject[];
int igMetaObject_RegisterClass();
int GuiLibrary_MarkRegistered();
int igMouseCursor_InitFields();

void igMouseCursor_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMouseCursor_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igMouseCursor_GetMetaObject,
        igMouseCursor_className,
        0x14, /* instance size */
        igMouseCursor_GetVTable,
        &igMouseCursor_InitFields,
        0, /* extra callback item */
        g_igMouseCursor_callbackList /* callback list */
    );
}
