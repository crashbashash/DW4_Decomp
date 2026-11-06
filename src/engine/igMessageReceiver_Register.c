extern char igObject_GetMetaObject_ParentAccessor[];
extern char thunk_igMessageReceiver_GetMetaObject[];
extern char igObject_Register[];
extern char igMessageReceiver_className[];
extern char g_igMessageReceiver_metaObject[];
int InsightLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igMessageReceiver_Register(void) {
    InsightLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igMessageReceiver_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igMessageReceiver_GetMetaObject,
        igMessageReceiver_className,
        8, /* instance size */
        0,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
