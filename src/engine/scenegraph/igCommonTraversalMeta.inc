igMetaObject *FUN_001a38e0(void) {
    if (g_igCommonTraversal_metaObject[0] == 0) {
        g_igCommonTraversal_metaObject[0] = ((igMetaObject *)igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0])));
    }
    return g_igCommonTraversal_metaObject[0];
}

