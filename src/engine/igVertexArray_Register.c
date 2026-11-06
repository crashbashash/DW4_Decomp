extern char igObject_GetMetaObject_ParentAccessor[];
extern char thunk_igVertexArray_GetMetaObject[];
extern char igObject_Register[];
extern char igVertexArray_className[];
extern char g_igVertexArray_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
int igVertexArray_InitFields();

void igVertexArray_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igVertexArray_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igVertexArray_GetMetaObject,
        igVertexArray_className,
        0x18, /* instance size */
        0,
        &igVertexArray_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
