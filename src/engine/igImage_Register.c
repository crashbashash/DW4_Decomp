extern char igObject_GetMetaObject_ParentAccessor[];
extern char thunk_igImage_GetMetaObject[];
extern char igObject_Register[];
extern char g_igImage_callbackList[];
extern char igImage_className[];
extern char g_igImage_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
extern int thunk_FUN_00156300[4];
int igImage_InitFields();

void igImage_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igImage_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igImage_GetMetaObject,
        igImage_className,
        0x5C, /* instance size */
        0,
        &igImage_InitFields,
        thunk_FUN_00156300, /* extra callback item */
        g_igImage_callbackList /* callback list */
    );
}
