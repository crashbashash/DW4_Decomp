extern char igOptInterface_GetVTable[];
extern char thunk_igOptInterface_GetMetaObject[];
extern char igInterface_GetPublishedMetaObject[];
extern char igInterface_Register[];
extern char g_igOptInterface_callbackList[];
extern char igOptInterface_className[];
extern char g_igOptInterface_metaObject[];
int BaseLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igOptInterface_InitFields();

void igOptInterface_Register(void) {
    BaseLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igOptInterface_metaObject,
        igInterface_Register,
        igInterface_GetPublishedMetaObject,
        thunk_igOptInterface_GetMetaObject,
        igOptInterface_className,
        0x30, /* instance size */
        igOptInterface_GetVTable,
        &igOptInterface_InitFields,
        0, /* extra callback item */
        g_igOptInterface_callbackList /* callback list */
    );
}
