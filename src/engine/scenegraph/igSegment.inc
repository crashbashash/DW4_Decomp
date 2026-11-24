namespace Gap {
namespace Sg {

igMetaObject *igSegment::_Meta;

igMetaObject *igSegment::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igSegment::retrieveVTablePointer()
{
    igSegment temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igSegment::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igSegment::arkRegisterInternal()
{
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Sg::igGroup::arkRegisterInternal,
        Gap::Sg::igGroup::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igSegment",
        sizeof(igSegment),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        0,
        0,
        0
    );
}
}
}

