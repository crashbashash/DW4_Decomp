extern char igInterfaced_GetPublishedMetaObject[];
extern char igInterfaced_Register[];
extern char thunk_igBase_GetMetaObject[];
extern char igBase_className[];
extern char g_igBase_metaObject[];
int BaseLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igBase_Register(void) {
    BaseLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igBase_metaObject,
        igInterfaced_Register,
        igInterfaced_GetPublishedMetaObject,
        thunk_igBase_GetMetaObject,
        igBase_className,
        0x20, /* instance size */
        0,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
