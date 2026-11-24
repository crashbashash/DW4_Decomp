namespace Gap {
namespace Sg {

igMetaObject *igModelViewMatrixAttrPool::_Meta;

igMetaObject *igModelViewMatrixAttrPool::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igModelViewMatrixAttrPool::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igModelViewMatrixAttrPool::retrieveVTablePointer()
{
    igModelViewMatrixAttrPool temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igModelViewMatrixAttrPool::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igModelViewMatrixAttrPool::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Attrs::igModelViewMatrixAttr::arkRegister, 0 };

    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Sg::igObjectPool::arkRegisterInternal,
        Gap::Sg::igObjectPool::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igModelViewMatrixAttrPool",
        sizeof(igModelViewMatrixAttrPool),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        0,
        0,
        regFunctions
    );
}
}
}

