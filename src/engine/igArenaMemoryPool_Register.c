extern char igMemoryPool_Register[];
extern char thunk_igArenaMemoryPool_GetMetaObject[];
extern char igMemoryPool_GetPublishedMetaObject[];
extern char igArenaMemoryPool_GetVTable[];
extern char g_igArenaMemoryPool_callbackList[];
extern char igArenaMemoryPool_className[];
extern char g_igArenaMemoryPool_metaObject[];
int igMetaObject_RegisterClass();
int igArenaMemoryPool_InitFields();

void igArenaMemoryPool_Register(void) {
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igArenaMemoryPool_metaObject,
        igMemoryPool_Register,
        igMemoryPool_GetPublishedMetaObject,
        thunk_igArenaMemoryPool_GetMetaObject,
        igArenaMemoryPool_className,
        0xD0, /* instance size */
        igArenaMemoryPool_GetVTable,
        &igArenaMemoryPool_InitFields,
        0, /* extra callback item */
        g_igArenaMemoryPool_callbackList /* callback list */
    );
}
