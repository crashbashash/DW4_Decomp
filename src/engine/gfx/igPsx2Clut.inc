namespace Gap {
namespace Gfx {

igMetaObject *igPsx2Clut::_Meta;
igMetaField *igPsx2Clut::k_id;
igMetaField *igPsx2Clut::k_refCount;
}
}

igMetaObject *igCapabilityManager_GetOrCreateMetaObject(void) {
    if (g_igCapabilityManager_metaObject == 0) {
        g_igCapabilityManager_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igCapabilityManager_metaObject;
}

