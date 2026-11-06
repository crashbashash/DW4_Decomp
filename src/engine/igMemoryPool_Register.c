extern char igObject_GetMetaObject_ParentAccessor[];
extern char thunk_igMemoryPool_GetMetaObject[];
extern char igObject_Register[];
extern char igMemoryPool_className[];
extern char g_igMemoryPool_metaObject[];
int igMetaObject_RegisterClass();
int igMemoryPool_InitFields();

void igMemoryPool_Register(void) {
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igMemoryPool_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igMemoryPool_GetMetaObject,
        igMemoryPool_className,
        0x70, /* instance size */
        0,
        &igMemoryPool_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
