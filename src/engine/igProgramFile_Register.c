extern char igObject_GetMetaObject_ParentAccessor[];
extern char igProgramFile_GetVTable[];
extern char thunk_igProgramFile_GetMetaObject[];
extern char igObject_Register[];
extern char g_igProgramFile_callbackList[];
extern char igProgramFile_className[];
extern char g_igProgramFile_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igProgramFile_InitFields();

void igProgramFile_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igProgramFile_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igProgramFile_GetMetaObject,
        igProgramFile_className,
        0x10, /* instance size */
        igProgramFile_GetVTable,
        &igProgramFile_InitFields,
        0, /* extra callback item */
        g_igProgramFile_callbackList /* callback list */
    );
}
