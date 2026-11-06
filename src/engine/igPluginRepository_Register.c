extern char igNamedObject_GetPublishedMetaObject[];
extern char igPluginRepository_GetVTable[];
extern char thunk_igPluginRepository_GetMetaObject[];
extern char igNamedObject_Register[];
extern char igPluginRepository_className[];
extern char g_igPluginRepository_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igPluginRepository_InitFields();

void igPluginRepository_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igPluginRepository_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        thunk_igPluginRepository_GetMetaObject,
        igPluginRepository_className,
        0x14, /* instance size */
        igPluginRepository_GetVTable,
        &igPluginRepository_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
