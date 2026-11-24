namespace Gap {
namespace Sg {

igMetaObject *igTextureMatrixAttrPool::_Meta;

igMetaObject *igTextureMatrixAttrPool::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igTextureMatrixAttrPool::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igTextureMatrixAttrPool::retrieveVTablePointer()
{
    igTextureMatrixAttrPool temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igTextureMatrixAttrPool::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igTextureMatrixAttrPool::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Attrs::igTextureMatrixAttr::arkRegister, 0 };

    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Sg::igObjectPool::arkRegisterInternal,
        Gap::Sg::igObjectPool::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igTextureMatrixAttrPool",
        sizeof(igTextureMatrixAttrPool),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        0,
        0,
        regFunctions
    );
}
}
}

