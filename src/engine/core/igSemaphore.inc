igMetaObject *g_igSemaphore_metaObject;

void * igSemaphore_Create(int pool) {
    igSemaphore_EnsureRegistered();
    return (void *)(igMetaObject_CreateInstance(g_igSemaphore_metaObject, (igMemoryPoolView *)pool));
}

igMetaObject *igSemaphore_GetOrCreateMetaObject(void) {
    if (g_igSemaphore_metaObject == 0) {
        g_igSemaphore_metaObject = (igMetaObject *)igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igSemaphore_metaObject;
}

igMetaObject *igSemaphore_GetMetaObject(void)
{
    igMetaObject *g = g_igSemaphore_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igSemaphore_EnsureRegistered();
    return g_igSemaphore_metaObject;
}

void igSemaphore_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igSemaphore_Register);
}

CallbackArray *igSemaphore_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1,
        &g_igSemaphore_metaObject,
        Gap::Core::igNamedObject::arkRegisterInternal,
        (igMetaObjectGetFunction)igNamedObject_GetPublishedMetaObject,
        igSemaphore_GetMetaObjectFunction,
        "igSemaphore",
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
    *(int *)((char *)((void *)g_igSemaphore_metaObject) + 60) = (int)(&igPsx2Semaphore_GetMetaObjectFunction);
}

