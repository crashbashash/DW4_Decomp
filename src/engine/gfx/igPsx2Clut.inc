igMetaObject *g_igPsx2Clut_metaObject;
igMetaField *g_igPsx2Clut_idMetaField;
igMetaField *g_igPsx2Clut_refCountMetaField;

void igPsx2Clut_GetMetaObjectFunction(void) {
    igPsx2Clut_GetMetaObject();
}

igMetaObject *igCapabilityManager_GetOrCreateMetaObject(void) {
    if (g_igCapabilityManager_metaObject == 0) {
        g_igCapabilityManager_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igCapabilityManager_metaObject;
}

