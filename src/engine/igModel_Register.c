extern char igObject_GetMetaObject_ParentAccessor[];
extern char igObject_Register[];
extern char igModel_GetVTable[];
extern char thunk_igModel_GetMetaObject[];
extern char g_igModel_callbackList[];
extern char igModel_className[];
extern char g_igModel_metaObject[];
int igMetaObject_RegisterClass();
int GuiLibrary_MarkRegistered();
int igModel_InitFields();

void igModel_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igModel_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igModel_GetMetaObject,
        igModel_className,
        0xC, /* instance size */
        igModel_GetVTable,
        &igModel_InitFields,
        0, /* extra callback item */
        g_igModel_callbackList /* callback list */
    );
}
