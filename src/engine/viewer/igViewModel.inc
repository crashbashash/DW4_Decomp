namespace Gap {
namespace Viewer {

igMetaObject *igViewModel::_Meta;
igMetaField *igViewModel::k_viewMatrix;
igMetaField *igViewModel::k_ratio;
igMetaField *igViewModel::k_hfov;
igMetaField *igViewModel::k_nearPlane;
igMetaField *igViewModel::k_farPlane;
igMetaField *igViewModel::k_position;
igMetaField *igViewModel::k_direction;
igMetaField *igViewModel::k_viewUpVector;
igMetaField *igViewModel::k_viewLeftVector;
igMetaField *igViewModel::k_sceneUpVector;
igMetaField *igViewModel::k_drawTime;
igMetaField *igViewModel::k_selectedCenter;
igMetaField *igViewModel::k_selectedLength;

igMetaObject *igViewModel::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igViewModel::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igViewModel::retrieveVTablePointer()
{
    igViewModel temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igViewModel::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igViewModel::arkRegisterInternal()
{
    ViewerLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Gui::igModel::arkRegisterInternal,
        Gap::Gui::igModel::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igViewModel",
        sizeof(igViewModel),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void igViewModel::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { (FieldFactory)Gap::Math::igMatrix44fMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Math::igVec3fMetaField::_instantiateFromPool, (FieldFactory)Gap::Math::igVec3fMetaField::_instantiateFromPool, (FieldFactory)Gap::Math::igVec3fMetaField::_instantiateFromPool, (FieldFactory)Gap::Math::igVec3fMetaField::_instantiateFromPool, (FieldFactory)Gap::Math::igVec3fMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igLongMetaField::_instantiateFromPool, (FieldFactory)Gap::Math::igVec3fMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool };
    static const char *names[] = { "_viewMatrix", "_ratio", "_hfov", "_nearPlane", "_farPlane", "_position", "_direction", "_viewUpVector", "_viewLeftVector", "_sceneUpVector", "_drawTime", "_selectedCenter", "_selectedLength" };
    static igMetaField **enumStorage[] = { &k_viewMatrix, &k_ratio, &k_hfov, &k_nearPlane, &k_farPlane, &k_position, &k_direction, &k_viewUpVector, &k_viewLeftVector, &k_sceneUpVector, &k_drawTime, &k_selectedCenter, &k_selectedLength };
    static int offsets[] = { 12, 76, 80, 84, 88, 92, 104, 116, 128, 140, 152, 160, 172 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 13);
    {
        igFloatMetaField *metaField = (igFloatMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->setDefault(1.0f);
    }
    {
        igFloatMetaField *metaField = (igFloatMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->setDefault(45.0f);
    }
    {
        igFloatMetaField *metaField = (igFloatMetaField *)igMetaObject_GetFieldAt(metaObject, start + 3);
        metaField->setDefault(1.0f);
    }
    {
        igFloatMetaField *metaField = (igFloatMetaField *)igMetaObject_GetFieldAt(metaObject, start + 4);
        metaField->setDefault(1000.0f);
    }
    {
        igVec3fMetaField *metaField = (igVec3fMetaField *)igMetaObject_GetFieldAt(metaObject, start + 5);
        metaField->setDefault(igVec3f(0.0f, 0.0f, 0.0f));
    }
    {
        igVec3fMetaField *metaField = (igVec3fMetaField *)igMetaObject_GetFieldAt(metaObject, start + 6);
        metaField->setDefault(igVec3f(0.0f, 0.0f, 1.0f));
    }
    {
        igVec3fMetaField *metaField = (igVec3fMetaField *)igMetaObject_GetFieldAt(metaObject, start + 7);
        metaField->setDefault(igVec3f(0.0f, 1.0f, 0.0f));
    }
    {
        igVec3fMetaField *metaField = (igVec3fMetaField *)igMetaObject_GetFieldAt(metaObject, start + 8);
        metaField->setDefault(igVec3f(1.0f, 0.0f, 0.0f));
    }
    {
        igVec3fMetaField *metaField = (igVec3fMetaField *)igMetaObject_GetFieldAt(metaObject, start + 9);
        metaField->setDefault(igVec3f(0.0f, 1.0f, 0.0f));
    }
    {
        igVec3fMetaField *metaField = (igVec3fMetaField *)igMetaObject_GetFieldAt(metaObject, start + 11);
        metaField->setDefault(igVec3f(0.0f, 0.0f, 0.0f));
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

