namespace Gap {
namespace Gui {

igMetaObject *igHotKeyEventReceiver::_Meta;
igMetaField *igHotKeyEventReceiver::k_hotKeyList;

igMetaObject *igHotKeyEventReceiver::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igHotKeyEventReceiver::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igHotKeyEventReceiver::retrieveVTablePointer()
{
    igHotKeyEventReceiver temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igHotKeyEventReceiver::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igHotKeyEventReceiver::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Gui::igHotKeyBindingList::arkRegister, 0 };

    GuiLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Gui::igEventReceiver::arkRegisterInternal,
        Gap::Gui::igEventReceiver::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igHotKeyEventReceiver",
        sizeof(igHotKeyEventReceiver),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igHotKeyEventReceiver::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create };
    static const char *names[] = { "_hotKeyList" };
    static igMetaField **enumStorage[] = { &k_hotKeyList };
    static int offsets[] = { 8 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 1);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)Gap::Gui::igHotKeyBindingList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

