extern char igObject_GetMetaObject_ParentAccessor[];
extern char igNamedObject_GetVTable[];
extern char thunk_igNamedObject_GetMetaObject[];
extern char igObject_Register[];
extern char igNamedObject_className[];
extern char g_igNamedObject_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igNamedObject_InitFields();

void igNamedObject_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igNamedObject_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igNamedObject_GetMetaObject,
        igNamedObject_className,
        0xC, /* instance size */
        igNamedObject_GetVTable,
        &igNamedObject_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
