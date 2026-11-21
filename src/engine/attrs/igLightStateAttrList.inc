namespace Gap {
namespace Attrs {

igMetaObject *igLightStateAttrList::_Meta;

igMetaObject *igLightStateAttrList::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igLightStateAttrList::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igLightStateAttrList::retrieveVTablePointer()
{
    igLightStateAttrList temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igLightStateAttrList::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igLightStateAttrList::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Attrs::igLightStateAttr::arkRegister, 0 };

    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igLightStateAttrList",
        sizeof(igLightStateAttrList),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        0,
        0,
        regFunctions
    );
}
}
}

