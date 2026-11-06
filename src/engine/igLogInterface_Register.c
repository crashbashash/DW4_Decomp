extern char igInterface_GetPublishedMetaObject[];
extern char igLogInterface_GetVTable[];
extern char thunk_igLogInterface_GetMetaObject[];
extern char igInterface_Register[];
extern char igLogInterface_className[];
extern char g_igLogInterface_metaObject[];
int BaseLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igLogInterface_InitFields();

void igLogInterface_Register(void) {
    BaseLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igLogInterface_metaObject,
        igInterface_Register,
        igInterface_GetPublishedMetaObject,
        thunk_igLogInterface_GetMetaObject,
        igLogInterface_className,
        0x24, /* instance size */
        igLogInterface_GetVTable,
        &igLogInterface_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
