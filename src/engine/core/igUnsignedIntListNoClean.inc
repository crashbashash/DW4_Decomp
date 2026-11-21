namespace Gap {
namespace Core {

igMetaObject *igUnsignedIntListNoClean::_Meta;
}
}

void * igUnsignedIntListNoClean_Create(int pool) {
    Gap::Core::igUnsignedIntListNoClean::arkRegister();
    return (void *)(igMetaObject_CreateInstance(Gap::Core::igUnsignedIntListNoClean::getClassMeta(), (igMemoryPoolView *)pool));
}

namespace Gap {
namespace Core {

igMetaObject *igUnsignedIntListNoClean::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igUnsignedIntListNoClean::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igUnsignedIntListNoClean::retrieveVTablePointer()
{
    igUnsignedIntListNoClean temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igUnsignedIntListNoClean::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igUnsignedIntListNoClean::arkRegisterInternal()
{
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igUnsignedIntList::arkRegisterInternal,
        Gap::Core::igUnsignedIntList::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igUnsignedIntListNoClean",
        sizeof(igUnsignedIntListNoClean),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        0,
        0,
        0
    );
}
}
}

