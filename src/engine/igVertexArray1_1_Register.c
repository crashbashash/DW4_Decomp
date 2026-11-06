extern char thunk_igVertexArray1_1_GetMetaObject[];
extern char igVertexArray_GetPublishedMetaObject[];
extern char igVertexArray_Register[];
extern char g_igVertexArray1_1_callbackList[];
extern char igVertexArray1_1_className[];
extern char g_igVertexArray1_1_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
extern int thunk_FUN_0015e010[4];
int igVertexArray1_1_InitFields();

void igVertexArray1_1_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igVertexArray1_1_metaObject,
        igVertexArray_Register,
        igVertexArray_GetPublishedMetaObject,
        thunk_igVertexArray1_1_GetMetaObject,
        igVertexArray1_1_className,
        0x30, /* instance size */
        0,
        &igVertexArray1_1_InitFields,
        thunk_FUN_0015e010, /* extra callback item */
        g_igVertexArray1_1_callbackList /* callback list */
    );
}
