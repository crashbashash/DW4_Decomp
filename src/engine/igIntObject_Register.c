extern char igObject_GetMetaObject_ParentAccessor[];
extern char igIntObject_GetVTable[];
extern char thunk_igIntObject_GetMetaObject[];
extern char igObject_Register[];
extern char igIntObject_className[];
extern char g_igIntObject_metaObject[];
int DataPumpLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igIntObject_InitFields();

void igIntObject_Register(void) {
    DataPumpLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igIntObject_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igIntObject_GetMetaObject,
        igIntObject_className,
        0xC, /* instance size */
        igIntObject_GetVTable,
        &igIntObject_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
