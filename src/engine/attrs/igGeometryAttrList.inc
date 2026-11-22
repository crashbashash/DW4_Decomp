namespace Gap {
namespace Attrs {

igMetaObject *igGeometryAttrList::_Meta;

igMetaObject *igGeometryAttrList::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igGeometryAttrList::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igGeometryAttrList::retrieveVTablePointer()
{
    igGeometryAttrList temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igGeometryAttrList::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igGeometryAttrList::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Attrs::igGeometryAttr::arkRegister, 0 };

    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igGeometryAttrList",
        sizeof(igGeometryAttrList),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        0,
        0,
        regFunctions
    );
}
}
}

