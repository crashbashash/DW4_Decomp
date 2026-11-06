extern char igObject_GetMetaObject_ParentAccessor[];
extern char igMessageFilter_GetVTable[];
extern char thunk_igMessageFilter_GetMetaObject[];
extern char igObject_Register[];
extern char g_igMessageFilter_callbackList[];
extern char igMessageFilter_className[];
extern char g_igMessageFilter_metaObject[];
int InsightLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igMessageFilter_InitFields();

void igMessageFilter_Register(void) {
    InsightLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMessageFilter_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igMessageFilter_GetMetaObject,
        igMessageFilter_className,
        0x10, /* instance size */
        igMessageFilter_GetVTable,
        &igMessageFilter_InitFields,
        0, /* extra callback item */
        g_igMessageFilter_callbackList /* callback list */
    );
}
