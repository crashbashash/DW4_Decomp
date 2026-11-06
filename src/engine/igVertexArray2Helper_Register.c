extern char igVertexArray2Helper_GetVTable[];
extern char thunk_igVertexArray2Helper_GetMetaObject[];
extern char igNamedObject_GetPublishedMetaObject[];
extern char igNamedObject_Register[];
extern char g_igVertexArray2Helper_callbackList[];
extern char igVertexArray2Helper_className[];
extern char g_igVertexArray2Helper_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
int igVertexArray2Helper_InitFields();

void igVertexArray2Helper_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igVertexArray2Helper_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        thunk_igVertexArray2Helper_GetMetaObject,
        igVertexArray2Helper_className,
        0x10, /* instance size */
        igVertexArray2Helper_GetVTable,
        &igVertexArray2Helper_InitFields,
        0, /* extra callback item */
        g_igVertexArray2Helper_callbackList /* callback list */
    );
}
