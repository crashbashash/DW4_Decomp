namespace Gap {
namespace Sg {

igMetaObject *igMatrixObjectPool::_Meta;

igMetaObject *igMatrixObjectPool::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igMatrixObjectPool::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igMatrixObjectPool::retrieveVTablePointer()
{
    igMatrixObjectPool temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igMatrixObjectPool::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igMatrixObjectPool::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { igMatrixObject_EnsureRegistered, 0 };

    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Sg::igObjectPool::arkRegisterInternal,
        Gap::Sg::igObjectPool::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igMatrixObjectPool",
        sizeof(igMatrixObjectPool),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        0,
        0,
        regFunctions
    );
}
}
}

