namespace Gap {
namespace Sg {

igMetaObject *igCommonTraversal::getClassTypeLazy() {
    if (_Meta == 0) {
        _Meta = ((igMetaObject *)igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return _Meta;
}
}
}

