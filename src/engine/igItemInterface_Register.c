extern char igInterface_GetPublishedMetaObject[];
extern char igItemInterface_GetVTable[];
extern char thunk_igItemInterface_GetMetaObject[];
extern char igInterface_Register[];
extern char g_igItemInterface_callbackList[];
extern char igItemInterface_className[];
extern char g_igItemInterface_metaObject[];
int BaseLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igItemInterface_InitFields();

void igItemInterface_Register(void) {
    BaseLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igItemInterface_metaObject,
        igInterface_Register,
        igInterface_GetPublishedMetaObject,
        thunk_igItemInterface_GetMetaObject,
        igItemInterface_className,
        0x34, /* instance size */
        igItemInterface_GetVTable,
        &igItemInterface_InitFields,
        0, /* extra callback item */
        g_igItemInterface_callbackList /* callback list */
    );
}
