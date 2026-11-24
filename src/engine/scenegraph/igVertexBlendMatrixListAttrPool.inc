namespace Gap {
namespace Sg {

igMetaObject *igVertexBlendMatrixListAttrPool::_Meta;

igMetaObject *igVertexBlendMatrixListAttrPool::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igVertexBlendMatrixListAttrPool::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igVertexBlendMatrixListAttrPool::retrieveVTablePointer()
{
    igVertexBlendMatrixListAttrPool temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igVertexBlendMatrixListAttrPool::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igVertexBlendMatrixListAttrPool::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { igVertexBlendMatrixListAttr_EnsureRegistered, 0 };

    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Sg::igObjectPool::arkRegisterInternal,
        Gap::Sg::igObjectPool::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igVertexBlendMatrixListAttrPool",
        sizeof(igVertexBlendMatrixListAttrPool),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        0,
        0,
        regFunctions
    );
}
}
}

