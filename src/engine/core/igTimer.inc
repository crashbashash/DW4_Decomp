void *igTimer_Create(int pool) {
    igTimer_EnsureRegistered();
    return (void *)igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x585788), (igMemoryPoolView *)pool);
}

igMetaObject *igTimer_GetOrCreateMetaObject(void) {
    if (g_igTimer_metaObject[0] == 0) {
        g_igTimer_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igTimer_metaObject[0];
}

igMetaObject *igTimer_GetMetaObject(void)
{
    igMetaObject *g = g_igTimer_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igTimer_EnsureRegistered();
    return g_igTimer_metaObject[0];
}

void igTimer_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igTimer_Register);
}

void igTimer_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1,
        g_igTimer_metaObject,
        (igMetaObjectRegisterFunction)igObject_Register,
        (igMetaObjectGetFunction)igObject_GetMetaObject_ParentAccessor,
        igTimer_GetMetaObjectFunction,
        igTimer_className,
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
    *(int *)((char *)(((void * *)g_igTimer_metaObject)[0]) + 60) = (int)(&igLongTimer_GetMetaObjectFunction);
}

void igLongTimer_GetMetaObjectFunction(void) {
    igLongTimer_GetMetaObject();
}

