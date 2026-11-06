extern char igNamedObject_GetPublishedMetaObject[];
extern char igVertexStream_GetVTable[];
extern char thunk_igVertexStream_GetMetaObject[];
extern char igNamedObject_Register[];
extern char g_igVertexStream_callbackList[];
extern char igVertexStream_className[];
extern char g_igVertexStream_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
int igVertexStream_InitFields();

void igVertexStream_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igVertexStream_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        thunk_igVertexStream_GetMetaObject,
        igVertexStream_className,
        0x24, /* instance size */
        igVertexStream_GetVTable,
        &igVertexStream_InitFields,
        0, /* extra callback item */
        g_igVertexStream_callbackList /* callback list */
    );
}
