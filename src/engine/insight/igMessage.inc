namespace Gap {
namespace Insight {

igMetaObject *igMessage::_Meta;

igMetaObject *igMessage::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igMessage::retrieveVTablePointer()
{
    igMessage temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igMessage::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igMessage::arkRegisterInternal()
{
    InsightLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igMessage",
        sizeof(igMessage),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        0,
        0,
        0
    );
}
}
}

