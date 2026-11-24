namespace Gap {
namespace Viewer {

igMetaObject *igViewerParameters::_Meta;
igMetaField *igViewerParameters::k_scene;
igMetaField *igViewerParameters::k_upVector;
igMetaField *igViewerParameters::k_ratio;
igMetaField *igViewerParameters::k_hfov;
igMetaField *igViewerParameters::k_nearPlane;
igMetaField *igViewerParameters::k_farPlane;
igMetaField *igViewerParameters::k_projectionMatrix;
igMetaField *igViewerParameters::k_viewMatrix;
igMetaField *igViewerParameters::k_drawTime;
igMetaField *igViewerParameters::k_sortTexture;
igMetaField *igViewerParameters::k_sortTransparent;
igMetaField *igViewerParameters::k_sortTransparentDistance;
igMetaField *igViewerParameters::k_transparencyMode;
igMetaField *igViewerParameters::k_useSceneLights;
igMetaField *igViewerParameters::k_useHeadLight;
igMetaField *igViewerParameters::k_useHeadLightSpecular;
igMetaField *igViewerParameters::k_alphaTest;
igMetaField *igViewerParameters::k_alphaTestForce;
igMetaField *igViewerParameters::k_backFaceCulling;
igMetaField *igViewerParameters::k_backFaceCullingForce;
igMetaField *igViewerParameters::k_wireframe;
igMetaField *igViewerParameters::k_wireframeForce;
igMetaField *igViewerParameters::k_flatShading;
igMetaField *igViewerParameters::k_flatShadingForce;
igMetaField *igViewerParameters::k_disables;
igMetaField *igViewerParameters::k_showGui;
igMetaField *igViewerParameters::k_showBoundingBox;
igMetaField *igViewerParameters::k_showNormals;
igMetaField *igViewerParameters::k_flushFrames;
igMetaField *igViewerParameters::k_operationMode;
igMetaField *igViewerParameters::k_firstCameraMode;
igMetaField *igViewerParameters::k_cameras;
igMetaField *igViewerParameters::k_beginTime;
igMetaField *igViewerParameters::k_endTime;
igMetaField *igViewerParameters::k_selectedObject;
igMetaField *igViewerParameters::k_timeOperation;
igMetaField *igViewerParameters::k_loopMode;
igMetaField *igViewerParameters::k_speed;
igMetaField *igViewerParameters::k_cursorPosition;

igMetaObject *igViewerParameters::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igViewerParameters::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igViewerParameters::retrieveVTablePointer()
{
    igViewerParameters temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igViewerParameters::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igViewerParameters::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Sg::igGroup::arkRegister, Gap::Core::igBitMask::arkRegister, Gap::Sg::igGraphPathList::arkRegister, Gap::Sg::igGraphPath::arkRegister, 0 };

    ViewerLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Gui::igModel::arkRegisterInternal,
        Gap::Gui::igModel::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igViewerParameters",
        sizeof(igViewerParameters),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igViewerParameters::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create, (FieldFactory)Gap::Math::igVec3fMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Math::igMatrix44fMetaField::_instantiateFromPool, (FieldFactory)Gap::Math::igMatrix44fMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igLongMetaField::_instantiateFromPool, igBoolMetaField_Create, igBoolMetaField_Create, igBoolMetaField_Create, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, igBoolMetaField_Create, igBoolMetaField_Create, igBoolMetaField_Create, igBoolMetaField_Create, igBoolMetaField_Create, igBoolMetaField_Create, igBoolMetaField_Create, igBoolMetaField_Create, igBoolMetaField_Create, igBoolMetaField_Create, igBoolMetaField_Create, igObjectRefMetaField_Create, igBoolMetaField_Create, igBoolMetaField_Create, igBoolMetaField_Create, igBoolMetaField_Create, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, igObjectRefMetaField_Create, (FieldFactory)Gap::Core::igLongMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igLongMetaField::_instantiateFromPool, igObjectRefMetaField_Create, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Math::igVec2fMetaField::_instantiateFromPool };
    static const char *names[] = { "_scene", "_upVector", "_ratio", "_hfov", "_nearPlane", "_farPlane", "_projectionMatrix", "_viewMatrix", "_drawTime", "_sortTexture", "_sortTransparent", "_sortTransparentDistance", "_transparencyMode", "_useSceneLights", "_useHeadLight", "_useHeadLightSpecular", "_alphaTest", "_alphaTestForce", "_backFaceCulling", "_backFaceCullingForce", "_wireframe", "_wireframeForce", "_flatShading", "_flatShadingForce", "_disables", "_showGui", "_showBoundingBox", "_showNormals", "_flushFrames", "_operationMode", "_firstCameraMode", "_cameras", "_beginTime", "_endTime", "_selectedObject", "_timeOperation", "_loopMode", "_speed", "_cursorPosition" };
    static igMetaField **enumStorage[] = { &k_scene, &k_upVector, &k_ratio, &k_hfov, &k_nearPlane, &k_farPlane, &k_projectionMatrix, &k_viewMatrix, &k_drawTime, &k_sortTexture, &k_sortTransparent, &k_sortTransparentDistance, &k_transparencyMode, &k_useSceneLights, &k_useHeadLight, &k_useHeadLightSpecular, &k_alphaTest, &k_alphaTestForce, &k_backFaceCulling, &k_backFaceCullingForce, &k_wireframe, &k_wireframeForce, &k_flatShading, &k_flatShadingForce, &k_disables, &k_showGui, &k_showBoundingBox, &k_showNormals, &k_flushFrames, &k_operationMode, &k_firstCameraMode, &k_cameras, &k_beginTime, &k_endTime, &k_selectedObject, &k_timeOperation, &k_loopMode, &k_speed, &k_cursorPosition };
    static int offsets[] = { 12, 16, 28, 32, 36, 40, 44, 108, 176, 184, 185, 186, 188, 192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 204, 208, 209, 210, 211, 212, 216, 220, 224, 232, 240, 244, 248, 252, 256 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 39);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)Gap::Sg::igGroup::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igVec3fMetaField *metaField = (igVec3fMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->setDefault(igVec3f(0.0f, 1.0f, 0.0f));
    }
    {
        igFloatMetaField *metaField = (igFloatMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->setDefault(1.0f);
    }
    {
        igFloatMetaField *metaField = (igFloatMetaField *)igMetaObject_GetFieldAt(metaObject, start + 3);
        metaField->setDefault(45.0f);
    }
    {
        igFloatMetaField *metaField = (igFloatMetaField *)igMetaObject_GetFieldAt(metaObject, start + 4);
        metaField->setDefault(1.0f);
    }
    {
        igFloatMetaField *metaField = (igFloatMetaField *)igMetaObject_GetFieldAt(metaObject, start + 5);
        metaField->setDefault(1000.0f);
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 12);
        metaField->setDefault(0);
    }
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 16);
        metaField->setDefault(1);
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 24);
        metaField->_metaObject = (int)Gap::Core::igBitMask::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 25);
        metaField->setDefault(1);
    }
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 26);
        metaField->setDefault(1);
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 29);
        metaField->setDefault(1);
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 30);
        metaField->setDefault(4);
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 31);
        metaField->_metaObject = (int)Gap::Sg::igGraphPathList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 34);
        metaField->_metaObject = (int)Gap::Sg::igGraphPath::getClassTypeLazy();
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 35);
        metaField->setDefault(1);
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 36);
        metaField->setDefault(2);
    }
    {
        igFloatMetaField *metaField = (igFloatMetaField *)igMetaObject_GetFieldAt(metaObject, start + 37);
        metaField->setDefault(1.0f);
    }
    {
        igVec2fMetaField *metaField = (igVec2fMetaField *)igMetaObject_GetFieldAt(metaObject, start + 38);
        metaField->setDefault(igVec2f(0.0f, 0.0f));
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

