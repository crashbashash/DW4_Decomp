extern char igObject_GetMetaObject_ParentAccessor[];
extern char igRegistryValue_GetVTable[];
extern char thunk_igRegistryValue_GetMetaObject[];
extern char igObject_Register[];
extern char g_igRegistryValue_callbackList[];
extern char igRegistryValue_className[];
extern char g_igRegistryValue_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igRegistryValue_InitFields();

void igRegistryValue_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igRegistryValue_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igRegistryValue_GetMetaObject,
        igRegistryValue_className,
        0x14, /* instance size */
        igRegistryValue_GetVTable,
        &igRegistryValue_InitFields,
        0, /* extra callback item */
        g_igRegistryValue_callbackList /* callback list */
    );
}
