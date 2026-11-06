extern char igIterator_Register[];
extern char igIterator_GetPublishedMetaObject[];
extern char igIterateDerived_GetVTable[];
extern char thunk_igIterateDerived_GetMetaObject[];
extern char g_igIterateDerived_callbackList[];
extern char igIterateDerived_className[];
extern char g_igIterateDerived_metaObject[];
int BaseLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igIterateDerived_InitFields();

void igIterateDerived_Register(void) {
    BaseLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igIterateDerived_metaObject,
        igIterator_Register,
        igIterator_GetPublishedMetaObject,
        thunk_igIterateDerived_GetMetaObject,
        igIterateDerived_className,
        0x10, /* instance size */
        igIterateDerived_GetVTable,
        &igIterateDerived_InitFields,
        0, /* extra callback item */
        g_igIterateDerived_callbackList /* callback list */
    );
}
