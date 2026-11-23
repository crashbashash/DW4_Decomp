namespace Gap {
namespace Gui {

igMetaObject *igRadioGroup::_Meta;
igMetaField *igRadioGroup::k_model;
igMetaField *igRadioGroup::k_selectedObserver;
igMetaField *igRadioGroup::k_observerList;
igMetaField *igRadioGroup::k_alwaysSelected;
igMetaField *igRadioGroup::k_lastSelected;
igMetaField *igRadioGroup::k_defaultSelected;

igMetaObject *igRadioGroup::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igRadioGroup::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igRadioGroup::retrieveVTablePointer()
{
    igRadioGroup temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igRadioGroup::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igRadioGroup::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Gui::igRadioGroupModel::arkRegister, Gap::Gui::igRadioGroupSelectedObserver::arkRegister, Gap::Gui::igOnOffValueObserverList::arkRegister, 0 };

    GuiLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igRadioGroup",
        sizeof(igRadioGroup),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igRadioGroup::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igBoolMetaField_Create, igIntMetaField_Create, igIntMetaField_Create };
    static const char *names[] = { "_model", "_selectedObserver", "_observerList", "_alwaysSelected", "_lastSelected", "_defaultSelected" };
    static igMetaField **enumStorage[] = { &k_model, &k_selectedObserver, &k_observerList, &k_alwaysSelected, &k_lastSelected, &k_defaultSelected };
    static int offsets[] = { 8, 12, 16, 20, 24, 28 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 6);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)Gap::Gui::igRadioGroupModel::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->_metaObject = (int)Gap::Gui::igRadioGroupSelectedObserver::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->_metaObject = (int)Gap::Gui::igOnOffValueObserverList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 3);
        metaField->setDefault(1);
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 4);
        metaField->setDefault(-1);
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

