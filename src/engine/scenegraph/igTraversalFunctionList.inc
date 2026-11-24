namespace Gap {
namespace Sg {

igTraversalFunctionList *igTraversalFunctionList::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igTraversalFunctionList *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igTraversalFunctionList::_Meta;

igMetaObject *igTraversalFunctionList::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igTraversalFunctionList::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igTraversalFunctionList::retrieveVTablePointer()
{
    igTraversalFunctionList temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igTraversalFunctionList::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igTraversalFunctionList::arkRegisterInternal()
{
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igDataList::arkRegisterInternal,
        Gap::Core::igDataList::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igTraversalFunctionList",
        sizeof(igTraversalFunctionList),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        0,
        0,
        0
    );
}
}
}
