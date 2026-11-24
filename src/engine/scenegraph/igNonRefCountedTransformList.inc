namespace Gap {
namespace Sg {

igMetaObject *igNonRefCountedTransformList::_Meta;

igMetaObject *igNonRefCountedTransformList::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igNonRefCountedTransformList::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igNonRefCountedTransformList::retrieveVTablePointer()
{
    igNonRefCountedTransformList temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igNonRefCountedTransformList::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igNonRefCountedTransformList::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Sg::igTransform::arkRegister, 0 };

    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igNonRefCountedObjectList::arkRegisterInternal,
        Gap::Core::igNonRefCountedObjectList::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igNonRefCountedTransformList",
        sizeof(igNonRefCountedTransformList),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        0,
        0,
        regFunctions
    );
}
}
}

