extern char igObject_GetMetaObject_ParentAccessor[];
extern char igFloatObject_GetVTable[];
extern char thunk_igFloatObject_GetMetaObject[];
extern char igObject_Register[];
extern char igFloatObject_className[];
extern char g_igFloatObject_metaObject[];
int DataPumpLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igFloatObject_InitFields();

void igFloatObject_Register(void) {
    DataPumpLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igFloatObject_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igFloatObject_GetMetaObject,
        igFloatObject_className,
        0xC, /* instance size */
        igFloatObject_GetVTable,
        &igFloatObject_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
