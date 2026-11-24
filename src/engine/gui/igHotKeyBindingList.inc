namespace Gap {
namespace Gui {

igMetaObject *igHotKeyBindingList::_Meta;

igMetaObject *igHotKeyBindingList::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igHotKeyBindingList::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igHotKeyBindingList::retrieveVTablePointer()
{
    igHotKeyBindingList temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igHotKeyBindingList::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igHotKeyBindingList::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Gui::igHotKeyBinding::arkRegister, 0 };

    GuiLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igHotKeyBindingList",
        sizeof(igHotKeyBindingList),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        0,
        0,
        regFunctions
    );
}
}
}

