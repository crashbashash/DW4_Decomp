extern char igObject_GetMetaObject_ParentAccessor[];
extern char thunk_igInsightPlugin_GetMetaObject[];
extern char igObject_Register[];
extern char igInsightPlugin_className[];
extern char g_igInsightPlugin_metaObject[];
int InsightLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igInsightPlugin_Register(void) {
    InsightLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igInsightPlugin_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igInsightPlugin_GetMetaObject,
        igInsightPlugin_className,
        8, /* instance size */
        0,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
