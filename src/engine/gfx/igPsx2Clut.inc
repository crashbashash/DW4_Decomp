namespace Gap {
namespace Gfx {

igMetaObject *igPsx2Clut::_Meta;
igMetaField *igPsx2Clut::k_id;
igMetaField *igPsx2Clut::k_refCount;

igMetaObject *igCapabilityManager::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}
}
}

