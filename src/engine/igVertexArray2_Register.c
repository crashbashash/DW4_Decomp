extern char igNamedObject_GetPublishedMetaObject[];
extern char igVertexArray2_GetVTable[];
extern char thunk_igVertexArray2_GetMetaObject[];
extern char igNamedObject_Register[];
extern char g_igVertexArray2_callbackList[];
extern char igVertexArray2_className[];
extern char g_igVertexArray2_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
int igVertexArray2_InitFields();

void igVertexArray2_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igVertexArray2_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        thunk_igVertexArray2_GetMetaObject,
        igVertexArray2_className,
        0x18, /* instance size */
        igVertexArray2_GetVTable,
        &igVertexArray2_InitFields,
        0, /* extra callback item */
        g_igVertexArray2_callbackList /* callback list */
    );
}
