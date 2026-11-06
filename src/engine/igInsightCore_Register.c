extern char igObject_GetMetaObject_ParentAccessor[];
extern char igInsightCore_GetVTable[];
extern char thunk_igInsightCore_GetMetaObject[];
extern char igObject_Register[];
extern char g_igInsightCore_callbackList[];
extern char igInsightCore_className[];
extern char g_igInsightCore_metaObject[];
int InsightLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
extern int thunk_FUN_00236140[4];
int igInsightCore_InitFields();

void igInsightCore_Register(void) {
    InsightLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igInsightCore_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igInsightCore_GetMetaObject,
        igInsightCore_className,
        0x70, /* instance size */
        igInsightCore_GetVTable,
        &igInsightCore_InitFields,
        thunk_FUN_00236140, /* extra callback item */
        g_igInsightCore_callbackList /* callback list */
    );
}
