void * igSemaphore_Create(int arg0) {
    igSemaphore_EnsureRegistered();
    return (void *)(igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x585970), (igMemoryPoolView *)arg0));
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
        1, /* abstract */
        ((char *)g_igSemaphore_metaObject),
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        igSemaphore_GetMetaObjectFunction,
        igSemaphore_className,
        0xC, /* instance size */
        0,
        &igSemaphore_InitFields_002ba7c0[0],
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igSemaphore_GetMetaObjectFunction(void) {
    igSemaphore_GetMetaObject();
}

void igSemaphore_SetAbstractProxy(void) {
    *(int *)((char *)(((void * *)g_igSemaphore_metaObject)[0]) + 60) = (int)(&igPsx2Semaphore_GetMetaObjectFunction);
}

