namespace Gap {
namespace Gui {

igMetaObject *igEventReceiverOrderedList::_Meta;

igMetaObject *igEventReceiverOrderedList::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igEventReceiverOrderedList::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igEventReceiverOrderedList::retrieveVTablePointer()
{
    igEventReceiverOrderedList temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igEventReceiverOrderedList::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igEventReceiverOrderedList::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Gui::igEventReceiver::arkRegister, 0 };

    GuiLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igDependencyOrderedList::arkRegisterInternal,
        Gap::Core::igDependencyOrderedList::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igEventReceiverOrderedList",
        sizeof(igEventReceiverOrderedList),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        0,
        0,
        regFunctions
    );
}
}
}

