extern char igObject_GetMetaObject_ParentAccessor[];
extern char igBoolObject_GetVTable[];
extern char thunk_igBoolObject_GetMetaObject[];
extern char igObject_Register[];
extern char igBoolObject_className[];
extern char g_igBoolObject_metaObject[];
int DataPumpLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igBoolObject_InitFields();

void igBoolObject_Register(void) {
    DataPumpLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igBoolObject_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igBoolObject_GetMetaObject,
        igBoolObject_className,
        0xC, /* instance size */
        igBoolObject_GetVTable,
        &igBoolObject_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
