extern char igMemoryPool_Register[];
extern char igMemoryPool_GetPublishedMetaObject[];
extern char igStackMemoryPool_GetVTable[];
extern char thunk_igStackMemoryPool_GetMetaObject[];
extern char g_igStackMemoryPool_callbackList[];
extern char igStackMemoryPool_className[];
extern char g_igStackMemoryPool_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igStackMemoryPool_InitFields();

void igStackMemoryPool_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igStackMemoryPool_metaObject,
        igMemoryPool_Register,
        igMemoryPool_GetPublishedMetaObject,
        thunk_igStackMemoryPool_GetMetaObject,
        igStackMemoryPool_className,
        0x98, /* instance size */
        igStackMemoryPool_GetVTable,
        &igStackMemoryPool_InitFields,
        0, /* extra callback item */
        g_igStackMemoryPool_callbackList /* callback list */
    );
}
