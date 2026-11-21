namespace Gap {
namespace Core {

igMetaObject *igMedia::_Meta;

igMetaObject *igMedia::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igMedia::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void igMedia::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igMedia::arkRegisterInternal()
{
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        true,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igMedia",
        sizeof(igMedia),
        0,
        &arkRegisterInitialize,
        (igMetaObjectCallback)Gap::Core::igMedia::userRegister,
        0
    );
}

void igMedia::arkRegisterInitialize()
{
    _Meta->_abstractProxy = (int)&igPsx2Media_GetMetaObjectFunction;
    igMetaObject_AddExitCallback((int)&_classDestructor);
}
}
}

