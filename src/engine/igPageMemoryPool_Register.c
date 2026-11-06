extern char igMemoryPool_Register[];
extern char igMemoryPool_GetPublishedMetaObject[];
extern char igPageMemoryPool_GetVTable[];
extern char thunk_igPageMemoryPool_GetMetaObject[];
extern char g_igPageMemoryPool_callbackList[];
extern char igPageMemoryPool_className[];
extern char g_igPageMemoryPool_metaObject[];
int igMetaObject_RegisterClass();
int igPageMemoryPool_InitFields();

void igPageMemoryPool_Register(void) {
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igPageMemoryPool_metaObject,
        igMemoryPool_Register,
        igMemoryPool_GetPublishedMetaObject,
        thunk_igPageMemoryPool_GetMetaObject,
        igPageMemoryPool_className,
        0x110, /* instance size */
        igPageMemoryPool_GetVTable,
        &igPageMemoryPool_InitFields,
        0, /* extra callback item */
        g_igPageMemoryPool_callbackList /* callback list */
    );
}
