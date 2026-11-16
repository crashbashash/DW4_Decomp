igMetaObject *g_igMedia_metaObject;

igMetaObject *igMedia_GetOrCreateMetaObject(void) {
    if (g_igMedia_metaObject == 0) {
        g_igMedia_metaObject = (igMetaObject *)igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igMedia_metaObject;
}

igMetaObject *igMedia_GetMetaObject(void)
{
    igMetaObject *g = g_igMedia_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igMedia_EnsureRegistered();
    return g_igMedia_metaObject;
}

void igMedia_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igMedia_Register);
}

CallbackArray *igMedia_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1,
        &g_igMedia_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        igMedia_GetMetaObjectFunction,
        "igMedia",
        8,
        0,
        igMedia_SetAbstractProxy,
        igMedia_StaticInitCallback,
        0
    );
}

void igMedia_GetMetaObjectFunction(void) {
    igMedia_GetMetaObject();
}

void igMedia_SetAbstractProxy(void) {
    *(int *)((char *)(((int)g_igMedia_metaObject)) + 60) = (int)&igPsx2Media_GetMetaObjectFunction;
    igMetaObject_AddExitCallback((int)&igMedia_ExitCallback);
}

