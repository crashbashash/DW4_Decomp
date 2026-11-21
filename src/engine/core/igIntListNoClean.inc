namespace Gap {
namespace Core {

igMetaObject *igIntListNoClean::_Meta;
}
}

void * igIntListNoClean_Create(int allocator) {
    Gap::Core::igIntListNoClean::arkRegister();
    return (void *)(igMetaObject_CreateInstance(Gap::Core::igIntListNoClean::getClassMeta(), (igMemoryPoolView *)allocator));
}

namespace Gap {
namespace Core {

igMetaObject *igIntListNoClean::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igIntListNoClean::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igIntListNoClean::retrieveVTablePointer()
{
    igIntListNoClean temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igIntListNoClean::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igIntListNoClean::arkRegisterInternal()
{
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igIntList::arkRegisterInternal,
        Gap::Core::igIntList::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igIntListNoClean",
        sizeof(igIntListNoClean),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        0,
        0,
        0
    );
}
}
}

