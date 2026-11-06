extern char igBase_GetPublishedMetaObject[];
extern char igListenerBase_GetVTable[];
extern char thunk_igListenerBase_GetMetaObject[];
extern char igBase_Register[];
extern char igListenerBase_className[];
extern char g_igListenerBase_metaObject[];
int BaseLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igListenerBase_Register(void) {
    BaseLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igListenerBase_metaObject,
        igBase_Register,
        igBase_GetPublishedMetaObject,
        thunk_igListenerBase_GetMetaObject,
        igListenerBase_className,
        0x20, /* instance size */
        igListenerBase_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
