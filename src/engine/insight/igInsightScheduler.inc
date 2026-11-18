igMetaObject *g_igInsightScheduler_metaObject;

igMetaObject *igInsightScheduler_GetOrCreateMetaObject(void) {
    if (g_igInsightScheduler_metaObject == 0) {
        g_igInsightScheduler_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igInsightScheduler_metaObject;
}

igMetaObject *igInsightScheduler_GetMetaObject(void)
{
    igMetaObject *g = g_igInsightScheduler_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igInsightScheduler_EnsureRegistered();
    return g_igInsightScheduler_metaObject;
}

void igInsightScheduler_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igInsightScheduler_Register);
}

CallbackArray *igInsightScheduler_Register(void) {
    InsightLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_igInsightScheduler_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        igInsightScheduler_GetMetaObjectFunction,
        "igInsightScheduler",
        8, /* instance size */
        0,
        igInsightScheduler_SetAbstractProxy_002325a0, /* post-init hook */
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igInsightScheduler_GetMetaObjectFunction(void) {
    igInsightScheduler_GetMetaObject();
}

void igInsightScheduler_SetAbstractProxy(void) {
    *(int *)((char *)(g_igInsightScheduler_metaObject) + 60) = (int)(&igSerialScheduler_GetMetaObjectFunction);
}

