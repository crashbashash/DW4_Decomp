extern char igObject_GetMetaObject_ParentAccessor[];
extern char igObjectStringMap_GetVTable[];
extern char thunk_igObjectStringMap_GetMetaObject[];
extern char igObject_Register[];
extern char g_igObjectStringMap_callbackList[];
extern char igObjectStringMap_className[];
extern char g_igObjectStringMap_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igObjectStringMap_InitFields();

void igObjectStringMap_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igObjectStringMap_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igObjectStringMap_GetMetaObject,
        igObjectStringMap_className,
        0x10, /* instance size */
        igObjectStringMap_GetVTable,
        &igObjectStringMap_InitFields,
        0, /* extra callback item */
        g_igObjectStringMap_callbackList /* callback list */
    );
}
