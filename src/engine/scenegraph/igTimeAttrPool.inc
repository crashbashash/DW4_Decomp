namespace Gap {
namespace Sg {

igMetaObject *igTimeAttrPool::_Meta;

igMetaObject *igTimeAttrPool::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igTimeAttrPool::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igTimeAttrPool::retrieveVTablePointer()
{
    igTimeAttrPool temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igTimeAttrPool::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igTimeAttrPool::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Attrs::igTimeAttr::arkRegister, 0 };

    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Sg::igObjectPool::arkRegisterInternal,
        Gap::Sg::igObjectPool::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igTimeAttrPool",
        sizeof(igTimeAttrPool),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        0,
        0,
        regFunctions
    );
}
}
}

