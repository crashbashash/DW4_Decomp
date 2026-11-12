igMetaObject *FUN_00232470(void) {
    if (g_igInsightScheduler_metaObject[0] == 0) {
        g_igInsightScheduler_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igInsightScheduler_metaObject[0];
}

igMetaObject *igInsightScheduler_GetMetaObject(void)
{
    igMetaObject *g = g_igInsightScheduler_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00232510();
    return g_igInsightScheduler_metaObject[0];
}

void FUN_00232510(void)
{
    igMetaObject_RunStaticInit(igInsightScheduler_Register);
}

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

void thunk_igInsightScheduler_GetMetaObject(void) {
    igInsightScheduler_GetMetaObject();
}

void FUN_002325a0(void) {
    *(int *)((char *)(g_igInsightScheduler_metaObject[0]) + 60) = (int)(&thunk_igSerialScheduler_GetMetaObject);
}

