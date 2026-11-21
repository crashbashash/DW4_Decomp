namespace Gap {
namespace Core {

igMetaObject *igTimer::_Meta;

igTimer *igTimer::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igTimer *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igTimer::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igTimer::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void igTimer::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igTimer::arkRegisterInternal()
{
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        true,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igTimer",
        sizeof(igTimer),
        0,
        &arkRegisterInitialize,
        0,
        0
    );
}

void igTimer::arkRegisterInitialize()
{
    _Meta->_abstractProxy = (int)&igLongTimer_GetMetaObjectFunction;
}
}
}

void igLongTimer_GetMetaObjectFunction(void) {
    igLongTimer_GetMetaObject();
}

