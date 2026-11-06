extern char igObject_GetMetaObject_ParentAccessor[];
extern char igObject_Register[];
extern char thunk_igView_GetMetaObject[];
extern char g_igView_callbackList[];
extern char igView_className[];
extern char g_igView_metaObject[];
int igMetaObject_RegisterClass();
int GuiLibrary_MarkRegistered();
int igView_InitFields();

void igView_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igView_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igView_GetMetaObject,
        igView_className,
        0xC, /* instance size */
        0,
        &igView_InitFields,
        0, /* extra callback item */
        g_igView_callbackList /* callback list */
    );
}
