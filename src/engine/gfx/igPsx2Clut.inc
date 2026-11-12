void thunk_igPsx2Clut_GetMetaObject(void) {
    igPsx2Clut_GetMetaObject();
}

igMetaObject *FUN_0014fd40(void) {
    if (g_igCapabilityManager_metaObject[0] == 0) {
        g_igCapabilityManager_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igCapabilityManager_metaObject[0];
}

