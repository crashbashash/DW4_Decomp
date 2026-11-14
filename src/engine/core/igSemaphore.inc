void * igSemaphore_Create(int pool) {
    igSemaphore_EnsureRegistered();
    return (void *)(igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x585970), (igMemoryPoolView *)pool));
}

igMetaObject *igSemaphore_GetOrCreateMetaObject(void) {
    if (g_igSemaphore_metaObject[0] == 0) {
        g_igSemaphore_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igSemaphore_metaObject[0];
}

igMetaObject *igSemaphore_GetMetaObject(void)
{
    igMetaObject *g = g_igSemaphore_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igSemaphore_EnsureRegistered();
    return g_igSemaphore_metaObject[0];
}

void igSemaphore_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igSemaphore_Register);
}

void igSemaphore_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1,
        g_igSemaphore_metaObject,
        (igMetaObjectRegisterFunction)igNamedObject_Register,
        (igMetaObjectGetFunction)igNamedObject_GetPublishedMetaObject,
        igSemaphore_GetMetaObjectFunction,
        igSemaphore_className,
        0xC,
        0,
        igSemaphore_SetAbstractProxy,
        0,
        0
    );
}

void igSemaphore_GetMetaObjectFunction(void) {
    igSemaphore_GetMetaObject();
}

void igSemaphore_SetAbstractProxy(void) {
    *(int *)((char *)(((void * *)g_igSemaphore_metaObject)[0]) + 60) = (int)(&igPsx2Semaphore_GetMetaObjectFunction);
}

