extern char igObject_GetMetaObject_ParentAccessor[];
extern char igMatrixObject_GetVTable[];
extern char thunk_igMatrixObject_GetMetaObject[];
extern char igObject_Register[];
extern char igMatrixObject_className[];
extern char g_igMatrixObject_metaObject[];
int DataPumpLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igMatrixObject_InitFields();

void igMatrixObject_Register(void) {
    DataPumpLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMatrixObject_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igMatrixObject_GetMetaObject,
        igMatrixObject_className,
        0x48, /* instance size */
        igMatrixObject_GetVTable,
        &igMatrixObject_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
