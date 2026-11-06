extern char igObject_GetMetaObject_ParentAccessor[];
extern char igMessage_GetVTable[];
extern char thunk_igMessage_GetMetaObject[];
extern char igObject_Register[];
extern char igMessage_className[];
extern char g_igMessage_metaObject[];
int InsightLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igMessage_Register(void) {
    InsightLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMessage_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igMessage_GetMetaObject,
        igMessage_className,
        8, /* instance size */
        igMessage_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
