igMetaObject *g_igTimer_metaObject;

igTimer *igTimer_Create(int allocator) {
    igTimer_EnsureRegistered();
    return (igTimer *)igMetaObject_CreateInstance(g_igTimer_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *igTimer_GetOrCreateMetaObject(void) {
    if (g_igTimer_metaObject == 0) {
        g_igTimer_metaObject = (igMetaObject *)igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igTimer_metaObject;
}

igMetaObject *igTimer_GetMetaObject(void)
{
    igMetaObject *g = g_igTimer_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igTimer_EnsureRegistered();
    return g_igTimer_metaObject;
}

void igTimer_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igTimer_Register);
}

CallbackArray *igTimer_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1,
        &g_igTimer_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        igTimer_GetMetaObjectFunction,
        "igTimer",
        8,
        0,
        igTimer_SetAbstractProxy,
        0,
        0
    );
}

void igTimer_GetMetaObjectFunction(void) {
    igTimer_GetMetaObject();
}

void igTimer_SetAbstractProxy(void) {
    *(int *)((char *)((void *)g_igTimer_metaObject) + 60) = (int)(&igLongTimer_GetMetaObjectFunction);
}

void igLongTimer_GetMetaObjectFunction(void) {
    igLongTimer_GetMetaObject();
}

