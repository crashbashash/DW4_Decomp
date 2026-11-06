extern char thunk_igOptBase_GetMetaObject[];
extern char igBase_GetPublishedMetaObject[];
extern char igBase_Register[];
extern char g_igOptBase_callbackList[];
extern char igOptBase_className[];
extern char g_igOptBase_metaObject[];
int BaseLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igOptBase_InitFields();

void igOptBase_Register(void) {
    BaseLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igOptBase_metaObject,
        igBase_Register,
        igBase_GetPublishedMetaObject,
        thunk_igOptBase_GetMetaObject,
        igOptBase_className,
        0x28, /* instance size */
        0,
        &igOptBase_InitFields,
        0, /* extra callback item */
        g_igOptBase_callbackList /* callback list */
    );
}
