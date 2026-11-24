namespace Gap {
namespace Gui {

igMetaObject *igGuiComponent::_Meta;
igMetaField *igGuiComponent::k_controller;
igMetaField *igGuiComponent::k_model;
igMetaField *igGuiComponent::k_aspect;
igMetaField *igGuiComponent::k_parent;
igMetaField *igGuiComponent::k_guiSystem;
igMetaField *igGuiComponent::k_node;
igMetaField *igGuiComponent::k_linked;

igMetaObject *igGuiComponent::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igGuiComponent::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igGuiComponent::retrieveVTablePointer()
{
    igGuiComponent temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}
}
}

namespace Gap {
namespace Gui {

void igGuiComponent::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igGuiComponent::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { igGuiComponentController_EnsureRegistered, Gap::Gui::igGuiComponentModel::arkRegister, igGuiComponentAspect_EnsureRegistered, Gap::Gui::igGuiSystem::arkRegister, igGuiComponentNode_RunStaticInit, 0 };

    GuiLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igGuiComponent",
        sizeof(igGuiComponent),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igGuiComponent::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igBoolMetaField_Create };
    static const char *names[] = { "_controller", "_model", "_aspect", "_parent", "_guiSystem", "_node", "_linked" };
    static igMetaField **enumStorage[] = { &k_controller, &k_model, &k_aspect, &k_parent, &k_guiSystem, &k_node, &k_linked };
    static int offsets[] = { 12, 16, 20, 24, 8, 28, 32 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 7);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)igGuiComponentController_GetOrCreateMetaObject();
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->_metaObject = (int)Gap::Gui::igGuiComponentModel::getClassTypeLazy();
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->_metaObject = (int)igGuiComponentAspect_GetOrCreateMetaObject();
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 3);
        metaField->_metaObject = (int)getClassTypeLazy();
        metaField->_refCounted = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 4);
        metaField->_metaObject = (int)Gap::Gui::igGuiSystem::getClassTypeLazy();
        metaField->_refCounted = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 5);
        metaField->_metaObject = (int)igGuiComponentNode_GetOrCreateMetaObject();
        metaField->_construct = 1;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

