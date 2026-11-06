extern char igObject_GetMetaObject_ParentAccessor[];
extern char igMemoryDictionary_GetVTable[];
extern char thunk_igMemoryDictionary_GetMetaObject[];
extern char igObject_Register[];
extern char g_igMemoryDictionary_callbackList[];
extern char igMemoryDictionary_className[];
extern char g_igMemoryDictionary_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igMemoryDictionary_InitFields();

void igMemoryDictionary_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMemoryDictionary_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igMemoryDictionary_GetMetaObject,
        igMemoryDictionary_className,
        0x18, /* instance size */
        igMemoryDictionary_GetVTable,
        &igMemoryDictionary_InitFields,
        0, /* extra callback item */
        g_igMemoryDictionary_callbackList /* callback list */
    );
}
