namespace Gap {
namespace Gui {

igMetaObject *igEventReceiver::_Meta;

igMetaObject *igEventReceiver::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igEventReceiver::retrieveVTablePointer()
{
    igEventReceiver temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igEventReceiver::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igEventReceiver::arkRegisterInternal()
{
    GuiLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igEventReceiver",
        sizeof(igEventReceiver),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        0,
        0,
        0
    );
}
}
}

