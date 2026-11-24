namespace Gap {
namespace Viewer {

igMetaObject *igPickMode::_Meta;
igMetaField *igPickMode::k_parameters;
igMetaField *igPickMode::k_guiSystem;
igMetaField *igPickMode::k_cursor;
igMetaField *igPickMode::k_savedCursor;
igMetaField *igPickMode::k_savedCursorState;
igMetaField *igPickMode::k_intersectTraversal;
igMetaField *igPickMode::k_ray;
igMetaField *igPickMode::k_impactLength;
igMetaField *igPickMode::k_hit;
igMetaField *igPickMode::k_hitPath;
igMetaField *igPickMode::k_inverseProjectionMatrix;
igMetaField *igPickMode::k_joystickT;

igPickMode *igPickMode::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igPickMode *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igPickMode::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igPickMode::retrieveVTablePointer()
{
    igPickMode temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igPickMode::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igPickMode::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Viewer::igViewerParameters::arkRegister, Gap::Gui::igGuiSystem::arkRegister, Gap::Gui::igMouseCursor::arkRegister, Gap::Sg::igIntersectTraversal::arkRegister, igRay_EnsureRegistered, Gap::Sg::igGraphPath::arkRegister, 0 };

    ViewerLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Viewer::igViewMode::arkRegisterInternal,
        Gap::Viewer::igViewMode::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igPickMode",
        sizeof(igPickMode),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igPickMode::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igBoolMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, igBoolMetaField_Create, igObjectRefMetaField_Create, (FieldFactory)Gap::Math::igMatrix44fMetaField::_instantiateFromPool, (FieldFactory)Gap::Math::igVec2fMetaField::_instantiateFromPool };
    static const char *names[] = { "_parameters", "_guiSystem", "_cursor", "_savedCursor", "_savedCursorState", "_intersectTraversal", "_ray", "_impactLength", "_hit", "_hitPath", "_inverseProjectionMatrix", "_joystickT" };
    static igMetaField **enumStorage[] = { &k_parameters, &k_guiSystem, &k_cursor, &k_savedCursor, &k_savedCursorState, &k_intersectTraversal, &k_ray, &k_impactLength, &k_hit, &k_hitPath, &k_inverseProjectionMatrix, &k_joystickT };
    static int offsets[] = { 76, 80, 84, 88, 92, 96, 100, 104, 108, 112, 116, 180 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 12);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)Gap::Viewer::igViewerParameters::getClassTypeLazy();
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->_metaObject = (int)Gap::Gui::igGuiSystem::getClassTypeLazy();
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->_metaObject = (int)Gap::Gui::igMouseCursor::getClassTypeLazy();
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 3);
        metaField->_metaObject = (int)Gap::Gui::igMouseCursor::getClassTypeLazy();
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 5);
        metaField->_metaObject = (int)Gap::Sg::igIntersectTraversal::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 6);
        metaField->_metaObject = (int)igRay_GetOrCreateMetaObject();
        metaField->_construct = 1;
    }
    {
        igFloatMetaField *metaField = (igFloatMetaField *)igMetaObject_GetFieldAt(metaObject, start + 7);
        metaField->setDefault(0.0f);
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 9);
        metaField->_metaObject = (int)Gap::Sg::igGraphPath::getClassTypeLazy();
    }
    {
        igVec2fMetaField *metaField = (igVec2fMetaField *)igMetaObject_GetFieldAt(metaObject, start + 11);
        metaField->setDefault(igVec2f(0.0f, 0.0f));
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

