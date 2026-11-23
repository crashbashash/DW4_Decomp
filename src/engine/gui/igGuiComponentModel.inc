namespace Gap {
namespace Gui {

igMetaObject *igGuiComponentModel::_Meta;
igMetaField *igGuiComponentModel::k_component;
igMetaField *igGuiComponentModel::k_enabled;
igMetaField *igGuiComponentModel::k_hasFocus;
igMetaField *igGuiComponentModel::k_mouseOver;
igMetaField *igGuiComponentModel::k_pushed;
igMetaField *igGuiComponentModel::k_size;
igMetaField *igGuiComponentModel::k_childHasFocus;

igMetaObject *igGuiComponentModel::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igGuiComponentModel::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igGuiComponentModel::retrieveVTablePointer()
{
    igGuiComponentModel temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igGuiComponentModel::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igGuiComponentModel::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { igGuiComponent_EnsureRegistered, 0 };

    GuiLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Gui::igModel::arkRegisterInternal,
        Gap::Gui::igModel::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igGuiComponentModel",
        sizeof(igGuiComponentModel),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}
}
}

namespace Gap {
namespace Gui {

void igGuiComponentModel::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create, igBoolMetaField_Create, igBoolMetaField_Create, igBoolMetaField_Create, igBoolMetaField_Create, (FieldFactory)Gap::Math::igVec3fMetaField::_instantiateFromPool, igBoolMetaField_Create };
    static const char *names[] = { "_component", "_enabled", "_hasFocus", "_mouseOver", "_pushed", "_size", "_childHasFocus" };
    static igMetaField **enumStorage[] = { &k_component, &k_enabled, &k_hasFocus, &k_mouseOver, &k_pushed, &k_size, &k_childHasFocus };
    static int offsets[] = { 32, 12, 13, 14, 15, 16, 28 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 7);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)igGuiComponent_GetOrCreateMetaObject();
        metaField->_refCounted = 0;
    }
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->setDefault(1);
    }
    {
        igVec3fMetaField *metaField = (igVec3fMetaField *)igMetaObject_GetFieldAt(metaObject, start + 5);
        metaField->setDefault(igVec3f(0.0f, 0.0f, 0.0f));
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

