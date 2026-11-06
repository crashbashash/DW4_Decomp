extern char igObject_GetMetaObject_ParentAccessor[];
extern char igStringObj_GetVTable[];
extern char thunk_igStringObj_GetMetaObject[];
extern char igObject_Register[];
extern char igStringObj_className[];
extern char g_igStringObj_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igStringObj_InitFields();

void igStringObj_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igStringObj_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igStringObj_GetMetaObject,
        igStringObj_className,
        0x10, /* instance size */
        igStringObj_GetVTable,
        &igStringObj_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
