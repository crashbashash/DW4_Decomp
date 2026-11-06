extern char igIterator_Register[];
extern char igIterator_GetPublishedMetaObject[];
extern char igIterateGraph_GetVTable[];
extern char thunk_igIterateGraph_GetMetaObject[];
extern char g_igIterateGraph_callbackList[];
extern char igIterateGraph_className[];
extern char g_igIterateGraph_metaObject[];
int BaseLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igIterateGraph_InitFields();

void igIterateGraph_Register(void) {
    BaseLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igIterateGraph_metaObject,
        igIterator_Register,
        igIterator_GetPublishedMetaObject,
        thunk_igIterateGraph_GetMetaObject,
        igIterateGraph_className,
        0x14, /* instance size */
        igIterateGraph_GetVTable,
        &igIterateGraph_InitFields,
        0, /* extra callback item */
        g_igIterateGraph_callbackList /* callback list */
    );
}
