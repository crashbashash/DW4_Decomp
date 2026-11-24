namespace Gap {
namespace Viewer {

igMetaObject *igFlyMode::_Meta;
igMetaField *igFlyMode::k_moveDirection;
igMetaField *igFlyMode::k_joystickT;
igMetaField *igFlyMode::k_joystickR;
igMetaField *igFlyMode::k_lastTranslation;
igMetaField *igFlyMode::k_lastRotation;
igMetaField *igFlyMode::k_speed;
igMetaField *igFlyMode::k_aiming;
igMetaField *igFlyMode::k_window;
igMetaField *igFlyMode::k_mousePos;
igMetaField *igFlyMode::k_lastAim;
igMetaField *igFlyMode::k_lastAimValid;

igFlyMode *igFlyMode::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igFlyMode *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igFlyMode::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igFlyMode::retrieveVTablePointer()
{
    igFlyMode temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igFlyMode::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igFlyMode::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { igWindow_EnsureRegistered, 0 };

    ViewerLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Viewer::igViewMode::arkRegisterInternal,
        Gap::Viewer::igViewMode::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igFlyMode",
        sizeof(igFlyMode),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igFlyMode::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { (FieldFactory)Gap::Math::igVec3fMetaField::_instantiateFromPool, (FieldFactory)Gap::Math::igVec3fMetaField::_instantiateFromPool, (FieldFactory)Gap::Math::igVec2fMetaField::_instantiateFromPool, (FieldFactory)Gap::Math::igVec3fMetaField::_instantiateFromPool, (FieldFactory)Gap::Math::igVec2fMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, igBoolMetaField_Create, igObjectRefMetaField_Create, (FieldFactory)Gap::Math::igVec2fMetaField::_instantiateFromPool, (FieldFactory)Gap::Math::igVec2fMetaField::_instantiateFromPool, igBoolMetaField_Create };
    static const char *names[] = { "_moveDirection", "_joystickT", "_joystickR", "_lastTranslation", "_lastRotation", "_speed", "_aiming", "_window", "_mousePos", "_lastAim", "_lastAimValid" };
    static igMetaField **enumStorage[] = { &k_moveDirection, &k_joystickT, &k_joystickR, &k_lastTranslation, &k_lastRotation, &k_speed, &k_aiming, &k_window, &k_mousePos, &k_lastAim, &k_lastAimValid };
    static int offsets[] = { 76, 88, 100, 108, 120, 128, 132, 136, 140, 148, 156 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 11);
    {
        igVec3fMetaField *metaField = (igVec3fMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->setDefault(igVec3f(0.0f, 0.0f, 0.0f));
    }
    {
        igVec3fMetaField *metaField = (igVec3fMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->setDefault(igVec3f(0.0f, 0.0f, 0.0f));
    }
    {
        igVec2fMetaField *metaField = (igVec2fMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->setDefault(igVec2f(0.0f, 0.0f));
    }
    {
        igVec3fMetaField *metaField = (igVec3fMetaField *)igMetaObject_GetFieldAt(metaObject, start + 3);
        metaField->setDefault(igVec3f(0.0f, 0.0f, 0.0f));
    }
    {
        igVec2fMetaField *metaField = (igVec2fMetaField *)igMetaObject_GetFieldAt(metaObject, start + 4);
        metaField->setDefault(igVec2f(0.0f, 0.0f));
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 7);
        metaField->_metaObject = (int)igWindow_GetOrCreateMetaObject();
    }
    {
        igVec2fMetaField *metaField = (igVec2fMetaField *)igMetaObject_GetFieldAt(metaObject, start + 8);
        metaField->setDefault(igVec2f(0.0f, 0.0f));
    }
    {
        igVec2fMetaField *metaField = (igVec2fMetaField *)igMetaObject_GetFieldAt(metaObject, start + 9);
        metaField->setDefault(igVec2f(0.0f, 0.0f));
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

