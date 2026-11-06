extern char igObject_GetMetaObject_ParentAccessor[];
extern char thunk_igInsightScheduler_GetMetaObject[];
extern char igObject_Register[];
extern char igInsightScheduler_className[];
extern char g_igInsightScheduler_metaObject[];
int InsightLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
extern int igInsightScheduler_SetAbstractProxy_002325a0[4];
void igInsightScheduler_Register(void) {
    InsightLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igInsightScheduler_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igInsightScheduler_GetMetaObject,
        igInsightScheduler_className,
        8, /* instance size */
        0,
        &igInsightScheduler_SetAbstractProxy_002325a0[0], /* post-init hook */
        0, /* extra callback item */
        0 /* callback list */
    );
}
