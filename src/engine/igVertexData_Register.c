extern char igNamedObject_GetPublishedMetaObject[];
extern char igVertexData_GetVTable[];
extern char thunk_igVertexData_GetMetaObject[];
extern char igNamedObject_Register[];
extern char g_igVertexData_callbackList[];
extern char igVertexData_className[];
extern char g_igVertexData_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
int igVertexData_InitFields();

void igVertexData_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igVertexData_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        thunk_igVertexData_GetMetaObject,
        igVertexData_className,
        0x24, /* instance size */
        igVertexData_GetVTable,
        &igVertexData_InitFields,
        0, /* extra callback item */
        g_igVertexData_callbackList /* callback list */
    );
}
