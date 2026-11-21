namespace Gap {
namespace Core {

igMetaObject *igCharListNoClean::_Meta;

igMetaObject *igCharListNoClean::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igCharListNoClean::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igCharListNoClean::retrieveVTablePointer()
{
    igCharListNoClean temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igCharListNoClean::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igCharListNoClean::arkRegisterInternal()
{
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igCharList::arkRegisterInternal,
        Gap::Core::igCharList::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igCharListNoClean",
        sizeof(igCharListNoClean),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        0,
        0,
        0
    );
}
}
}

