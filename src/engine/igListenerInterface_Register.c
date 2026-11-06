extern char igInterface_GetPublishedMetaObject[];
extern char igListenerInterface_GetVTable[];
extern char thunk_igListenerInterface_GetMetaObject[];
extern char igInterface_Register[];
extern char g_igListenerInterface_callbackList[];
extern char igListenerInterface_className[];
extern char g_igListenerInterface_metaObject[];
int BaseLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igListenerInterface_InitFields();

void igListenerInterface_Register(void) {
    BaseLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igListenerInterface_metaObject,
        igInterface_Register,
        igInterface_GetPublishedMetaObject,
        thunk_igListenerInterface_GetMetaObject,
        igListenerInterface_className,
        0x30, /* instance size */
        igListenerInterface_GetVTable,
        &igListenerInterface_InitFields,
        0, /* extra callback item */
        g_igListenerInterface_callbackList /* callback list */
    );
}
