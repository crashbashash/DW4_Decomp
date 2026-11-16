igMetaObject *FUN_001a38e0(void) {
    if (g_igCommonTraversal_metaObject == 0) {
        g_igCommonTraversal_metaObject = ((igMetaObject *)igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igCommonTraversal_metaObject;
}

