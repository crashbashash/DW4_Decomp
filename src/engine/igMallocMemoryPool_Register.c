extern char igMemoryPool_Register[];
extern char igMemoryPool_GetPublishedMetaObject[];
extern char igMallocMemoryPool_GetVTable[];
extern char thunk_igMallocMemoryPool_GetMetaObject[];
extern char g_igMallocMemoryPool_callbackList[];
extern char igMallocMemoryPool_className[];
extern char g_igMallocMemoryPool_metaObject[];
int igMetaObject_RegisterClass();
int igMallocMemoryPool_InitFields();

void igMallocMemoryPool_Register(void) {
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMallocMemoryPool_metaObject,
        igMemoryPool_Register,
        igMemoryPool_GetPublishedMetaObject,
        thunk_igMallocMemoryPool_GetMetaObject,
        igMallocMemoryPool_className,
        0xA0, /* instance size */
        igMallocMemoryPool_GetVTable,
        &igMallocMemoryPool_InitFields,
        0, /* extra callback item */
        g_igMallocMemoryPool_callbackList /* callback list */
    );
}
