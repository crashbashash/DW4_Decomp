igMetaObject *g_igMessageDispatcher_metaObject;

igMetaObject *igMessageDispatcher_GetOrCreateMetaObject(void) {
    if (g_igMessageDispatcher_metaObject == 0) {
        g_igMessageDispatcher_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igMessageDispatcher_metaObject;
}

igMetaObject *igMessageDispatcher_GetMetaObject(void)
{
    igMetaObject *g = g_igMessageDispatcher_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igMessageDispatcher_EnsureRegistered();
    return g_igMessageDispatcher_metaObject;
}

void igMessageDispatcher_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igMessageDispatcher_Register);
}

CallbackArray *igMessageDispatcher_Register(void) {
    InsightLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_igMessageDispatcher_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        igMessageDispatcher_GetMetaObjectFunction,
        "igMessageDispatcher",
        8, /* instance size */
        0,
        igMessageDispatcher_SetAbstractProxy_002321e0, /* post-init hook */
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igMessageDispatcher_GetMetaObjectFunction(void) {
    igMessageDispatcher_GetMetaObject();
}

void igMessageDispatcher_SetAbstractProxy(void) {
    *(int *)((char *)(g_igMessageDispatcher_metaObject) + 60) = (int)(&igFilterMessageDispatcher_GetMetaObjectFunction);
}

