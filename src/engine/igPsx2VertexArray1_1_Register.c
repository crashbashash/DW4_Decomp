extern char igVertexArray1_1_Register[];
extern char thunk_igPsx2VertexArray1_1_GetMetaObject[];
extern char igPsx2VertexArray1_1_GetVTable[];
extern char igVertexArray1_1_GetPublishedMetaObject[];
extern char g_igPsx2VertexArray1_1_callbackList[];
extern char igPsx2VertexArray1_1_className[];
extern char g_igPsx2VertexArray1_1_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
int igPsx2VertexArray1_1_InitFields();

void igPsx2VertexArray1_1_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igPsx2VertexArray1_1_metaObject,
        igVertexArray1_1_Register,
        igVertexArray1_1_GetPublishedMetaObject,
        thunk_igPsx2VertexArray1_1_GetMetaObject,
        igPsx2VertexArray1_1_className,
        0x90, /* instance size */
        igPsx2VertexArray1_1_GetVTable,
        &igPsx2VertexArray1_1_InitFields,
        0, /* extra callback item */
        g_igPsx2VertexArray1_1_callbackList /* callback list */
    );
}
