extern char igObject_GetMetaObject_ParentAccessor[];
extern char igFolder_GetVTable[];
extern char thunk_igFolder_GetMetaObject[];
extern char igObject_Register[];
extern char igFolder_className[];
extern char g_igFolder_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igFolder_InitFields();

void igFolder_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igFolder_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igFolder_GetMetaObject,
        igFolder_className,
        0xC, /* instance size */
        igFolder_GetVTable,
        &igFolder_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
