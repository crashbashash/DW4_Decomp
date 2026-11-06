extern char igVertexStream_Register[];
extern char thunk_igPsx2VertexStream_GetMetaObject[];
extern char igPsx2VertexStream_GetVTable[];
extern char igVertexStream_GetPublishedMetaObject[];
extern char thunk_FUN_0017f5a0[];
extern char igPsx2VertexStream_className[];
extern char g_igPsx2VertexStream_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
int igPsx2VertexStream_InitFields();

void igPsx2VertexStream_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igPsx2VertexStream_metaObject,
        igVertexStream_Register,
        igVertexStream_GetPublishedMetaObject,
        thunk_igPsx2VertexStream_GetMetaObject,
        igPsx2VertexStream_className,
        0x90, /* instance size */
        igPsx2VertexStream_GetVTable,
        &igPsx2VertexStream_InitFields,
        thunk_FUN_0017f5a0, /* extra callback item */
        0 /* callback list */
    );
}
