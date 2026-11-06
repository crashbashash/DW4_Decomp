extern char igInterfaced_GetPublishedMetaObject[];
extern char igInterfaced_Register[];
extern char igInterface_GetVTable[];
extern char thunk_igInterface_GetMetaObject[];
extern char igInterface_className[];
extern char g_igInterface_metaObject[];
int BaseLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igInterface_Register(void) {
    BaseLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igInterface_metaObject,
        igInterfaced_Register,
        igInterfaced_GetPublishedMetaObject,
        thunk_igInterface_GetMetaObject,
        igInterface_className,
        0x20, /* instance size */
        igInterface_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
