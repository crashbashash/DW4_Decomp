extern char igObject_GetMetaObject_ParentAccessor[];
extern char thunk_igDataPumpInterface_GetMetaObject[];
extern char igObject_Register[];
extern char igDataPumpInterface_className[];
extern char g_igDataPumpInterface_metaObject[];
int DataPumpLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igDataPumpInterface_Register(void) {
    DataPumpLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igDataPumpInterface_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igDataPumpInterface_GetMetaObject,
        igDataPumpInterface_className,
        8, /* instance size */
        0,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
