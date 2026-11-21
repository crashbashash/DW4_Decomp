namespace Gap {
namespace Attrs {

igMetaObject *igLightList::_Meta;

igMetaObject *igLightList::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igLightList::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igLightList::retrieveVTablePointer()
{
    igLightList temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igLightList::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igLightList::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Attrs::igLightAttr::arkRegister, 0 };

    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igLightList",
        sizeof(igLightList),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        0,
        0,
        regFunctions
    );
}
}
}

