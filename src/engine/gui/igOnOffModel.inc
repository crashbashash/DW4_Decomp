namespace Gap {
namespace Gui {

igMetaObject *igOnOffModel::_Meta;
igMetaField *igOnOffModel::k_value;

igMetaObject *igOnOffModel::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igOnOffModel::retrieveVTablePointer()
{
    igOnOffModel temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igOnOffModel::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igOnOffModel::arkRegisterInternal()
{
    GuiLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Gui::igGuiComponentModel::arkRegisterInternal,
        Gap::Gui::igGuiComponentModel::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igOnOffModel",
        sizeof(igOnOffModel),
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

void igOnOffModel::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igBoolMetaField_Create };
    static const char *names[] = { "_value" };
    static igMetaField **enumStorage[] = { &k_value };
    static int offsets[] = { 36 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 1);
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

