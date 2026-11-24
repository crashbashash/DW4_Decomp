namespace Gap {
namespace Sg {

igMetaObject *igRenderPackageList::_Meta;

igMetaObject *igRenderPackageList::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igRenderPackageList::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igRenderPackageList::retrieveVTablePointer()
{
    igRenderPackageList temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igRenderPackageList::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igRenderPackageList::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Sg::igRenderPackage::arkRegister, 0 };

    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igNonRefCountedObjectList::arkRegisterInternal,
        Gap::Core::igNonRefCountedObjectList::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igRenderPackageList",
        sizeof(igRenderPackageList),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        0,
        0,
        regFunctions
    );
}
}
}

