extern char igObject_GetMetaObject_ParentAccessor[];
extern char igPsx2IopRpcConnection_GetVTable[];
extern char thunk_igPsx2IopRpcConnection_GetMetaObject[];
extern char igObject_Register[];
extern char igPsx2IopRpcConnection_className[];
extern char g_igPsx2IopRpcConnection_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igPsx2IopRpcConnection_InitFields();

void igPsx2IopRpcConnection_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igPsx2IopRpcConnection_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igPsx2IopRpcConnection_GetMetaObject,
        igPsx2IopRpcConnection_className,
        0x14, /* instance size */
        igPsx2IopRpcConnection_GetVTable,
        &igPsx2IopRpcConnection_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
