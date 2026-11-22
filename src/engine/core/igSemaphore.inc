namespace Gap {
namespace Core {

igMetaObject *igSemaphore::_Meta;

igSemaphore *igSemaphore::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igSemaphore *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igSemaphore::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igSemaphore::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void igSemaphore::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igSemaphore::arkRegisterInternal()
{
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        true,
        &_Meta,
        Gap::Core::igNamedObject::arkRegisterInternal,
        Gap::Core::igNamedObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igSemaphore",
        sizeof(igSemaphore),
        0,
        &arkRegisterInitialize,
        0,
        0
    );
}

void igSemaphore::arkRegisterInitialize()
{
    _Meta->_abstractProxy = (int)&igPsx2Semaphore_GetMetaObjectFunction;
}
}
}

