namespace Gap {
namespace Gui {

igMetaObject *igGuiSystemModel::_Meta;
igMetaField *igGuiSystemModel::k_windowSize;
igMetaField *igGuiSystemModel::k_mousePosition;
igMetaField *igGuiSystemModel::k_mousePressed;
igMetaField *igGuiSystemModel::k_viewMatrix;
igMetaField *igGuiSystemModel::k_projectionMatrix;
igMetaField *igGuiSystemModel::k_active;
igMetaField *igGuiSystemModel::k_rootComponent;
igMetaField *igGuiSystemModel::k_focusedComponent;
igMetaField *igGuiSystemModel::k_componentUnderMouse;
igMetaField *igGuiSystemModel::k_pushedComponent;
igMetaField *igGuiSystemModel::k_windowCloseRequested;

igMetaObject *igGuiSystemModel::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igGuiSystemModel::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igGuiSystemModel::retrieveVTablePointer()
{
    igGuiSystemModel temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igGuiSystemModel::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igGuiSystemModel::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { igGuiComponent_EnsureRegistered, 0 };

    GuiLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Gui::igModel::arkRegisterInternal,
        Gap::Gui::igModel::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igGuiSystemModel",
        sizeof(igGuiSystemModel),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igGuiSystemModel::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { (FieldFactory)Gap::Math::igVec2fMetaField::_instantiateFromPool, (FieldFactory)Gap::Math::igVec2fMetaField::_instantiateFromPool, igBoolMetaField_Create, (FieldFactory)Gap::Math::igMatrix44fMetaField::_instantiateFromPool, (FieldFactory)Gap::Math::igMatrix44fMetaField::_instantiateFromPool, igBoolMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igBoolMetaField_Create };
    static const char *names[] = { "_windowSize", "_mousePosition", "_mousePressed", "_viewMatrix", "_projectionMatrix", "_active", "_rootComponent", "_focusedComponent", "_componentUnderMouse", "_pushedComponent", "_windowCloseRequested" };
    static igMetaField **enumStorage[] = { &k_windowSize, &k_mousePosition, &k_mousePressed, &k_viewMatrix, &k_projectionMatrix, &k_active, &k_rootComponent, &k_focusedComponent, &k_componentUnderMouse, &k_pushedComponent, &k_windowCloseRequested };
    static int offsets[] = { 12, 20, 28, 32, 96, 160, 164, 168, 172, 176, 180 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 11);
    {
        igVec2fMetaField *metaField = (igVec2fMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->setDefault(igVec2f(0.0f, 0.0f));
    }
    {
        igVec2fMetaField *metaField = (igVec2fMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->setDefault(igVec2f(0.0f, 0.0f));
    }
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 5);
        metaField->setDefault(1);
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 6);
        metaField->_metaObject = (int)igGuiComponent_GetOrCreateMetaObject();
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 7);
        metaField->_metaObject = (int)igGuiComponent_GetOrCreateMetaObject();
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 8);
        metaField->_metaObject = (int)igGuiComponent_GetOrCreateMetaObject();
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 9);
        metaField->_metaObject = (int)igGuiComponent_GetOrCreateMetaObject();
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

