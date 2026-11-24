namespace Gap {
namespace Gui {

igMetaObject *igBoxComponent::_Meta;

igMetaObject *igBoxComponent::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igBoxComponent::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igBoxComponent::retrieveVTablePointer()
{
    igBoxComponent temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igBoxComponent::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igBoxComponent::arkRegisterInternal()
{
    GuiLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Gui::igGuiComponent::arkRegisterInternal,
        Gap::Gui::igGuiComponent::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igBoxComponent",
        sizeof(igBoxComponent),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        0,
        0,
        0
    );
}
}
}

