namespace Gap {
namespace Sg {

igMetaObject *igEnvironmentMapShader2List::_Meta;

igMetaObject *igEnvironmentMapShader2List::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igEnvironmentMapShader2List::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igEnvironmentMapShader2List::retrieveVTablePointer()
{
    igEnvironmentMapShader2List temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igEnvironmentMapShader2List::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igEnvironmentMapShader2List::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Sg::igEnvironmentMapShader2::arkRegister, 0 };

    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igEnvironmentMapShader2List",
        sizeof(igEnvironmentMapShader2List),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        0,
        0,
        regFunctions
    );
}
}
}

