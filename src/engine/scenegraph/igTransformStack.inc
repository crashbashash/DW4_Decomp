namespace Gap {
namespace Sg {

igMetaObject *igTransformStack::_Meta;

igMetaObject *igTransformStack::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igTransformStack::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igTransformStack::retrieveVTablePointer()
{
    igTransformStack temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igTransformStack::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igTransformStack::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Sg::igTransform::arkRegister, 0 };

    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igNonRefCountedObjectStack::arkRegisterInternal,
        Gap::Core::igNonRefCountedObjectStack::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igTransformStack",
        sizeof(igTransformStack),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        0,
        0,
        regFunctions
    );
}
}
}

