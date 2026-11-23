namespace Gap {
namespace Gui {

igMetaObject *igRadioGroupModel::_Meta;
igMetaField *igRadioGroupModel::k_selected;

igMetaObject *igRadioGroupModel::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igRadioGroupModel::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igRadioGroupModel::retrieveVTablePointer()
{
    igRadioGroupModel temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igRadioGroupModel::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igRadioGroupModel::arkRegisterInternal()
{
    GuiLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Gui::igModel::arkRegisterInternal,
        Gap::Gui::igModel::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igRadioGroupModel",
        sizeof(igRadioGroupModel),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}
}
}

namespace Gap {
namespace Gui {

void igRadioGroupModel::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igIntMetaField_Create };
    static const char *names[] = { "_selected" };
    static igMetaField **enumStorage[] = { &k_selected };
    static int offsets[] = { 12 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 1);
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->setDefault(-1);
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

