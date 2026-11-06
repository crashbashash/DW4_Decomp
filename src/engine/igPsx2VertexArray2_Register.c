extern char igVertexArray2_Register[];
extern char thunk_igPsx2VertexArray2_GetMetaObject_0014acf0[];
extern char igPsx2VertexArray2_GetVTable[];
extern char igVertexArray2_GetPublishedMetaObject[];
extern char igPsx2VertexArray2_className[];
extern char g_igPsx2VertexArray2_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
extern int igPsx2VertexArray2_InitFields_00152350[4];
void igPsx2VertexArray2_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igPsx2VertexArray2_metaObject,
        igVertexArray2_Register,
        igVertexArray2_GetPublishedMetaObject,
        thunk_igPsx2VertexArray2_GetMetaObject_0014acf0,
        igPsx2VertexArray2_className,
        0x18, /* instance size */
        igPsx2VertexArray2_GetVTable,
        &igPsx2VertexArray2_InitFields_00152350[0],      /* Field adder. */
        0,                                               /* extra callback-vector item (none) */
        0                                                /* zero-terminated callback-vector item list (none) */
    );
}
