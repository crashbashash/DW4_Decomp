extern char igMemoryPool_Register[];
extern char igAliasMemoryPool_GetVTable[];
extern char thunk_igAliasMemoryPool_GetMetaObject[];
extern char igMemoryPool_GetPublishedMetaObject[];
extern char g_igAliasMemoryPool_callbackList[];
extern char igAliasMemoryPool_className[];
extern char g_igAliasMemoryPool_metaObject[];
int igMetaObject_RegisterClass();
int igAliasMemoryPool_InitFields();

void igAliasMemoryPool_Register(void) {
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igAliasMemoryPool_metaObject,
        igMemoryPool_Register,
        igMemoryPool_GetPublishedMetaObject,
        thunk_igAliasMemoryPool_GetMetaObject,
        igAliasMemoryPool_className,
        0xB8, /* instance size */
        igAliasMemoryPool_GetVTable,
        &igAliasMemoryPool_InitFields,
        0, /* extra callback item */
        g_igAliasMemoryPool_callbackList /* callback list */
    );
}
