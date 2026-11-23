namespace Gap {
namespace Gui {

igMetaObject *igRadioGroupSelectedObserver::_Meta;
igMetaField *igRadioGroupSelectedObserver::k_group;

igMetaObject *igRadioGroupSelectedObserver::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igRadioGroupSelectedObserver::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igRadioGroupSelectedObserver::retrieveVTablePointer()
{
    igRadioGroupSelectedObserver temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igRadioGroupSelectedObserver::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igRadioGroupSelectedObserver::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Gui::igRadioGroup::arkRegister, 0 };

    GuiLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Gui::igView::arkRegisterInternal,
        Gap::Gui::igView::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igRadioGroupSelectedObserver",
        sizeof(igRadioGroupSelectedObserver),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igRadioGroupSelectedObserver::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create };
    static const char *names[] = { "_group" };
    static igMetaField **enumStorage[] = { &k_group };
    static int offsets[] = { 12 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 1);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)Gap::Gui::igRadioGroup::getClassTypeLazy();
        metaField->_refCounted = 0;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

