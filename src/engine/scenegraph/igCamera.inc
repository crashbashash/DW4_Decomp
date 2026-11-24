namespace Gap {
namespace Sg {

igCamera *igCamera::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igCamera *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igCamera::_Meta;
igMetaField *igCamera::k_cameraType;
igMetaField *igCamera::k_horizontalFieldOfView;
igMetaField *igCamera::k_nearPlane;
igMetaField *igCamera::k_farPlane;
igMetaField *igCamera::k_deadfield1;
igMetaField *igCamera::k_deadfield2;
igMetaField *igCamera::k_deadfield3;

igMetaObject *igCamera::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igCamera::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igCamera::retrieveVTablePointer()
{
    igCamera temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igCamera::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igCamera::arkRegisterInternal()
{
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Sg::igNode::arkRegisterInternal,
        Gap::Sg::igNode::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igCamera",
        sizeof(igCamera),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void igCamera::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igEnumMetaField_Create, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, igBoolMetaField_Create, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool };
    static const char *names[] = { "_cameraType", "_horizontalFieldOfView", "_nearPlane", "_farPlane", "_deadfield1", "_deadfield2", "_deadfield3" };
    static igMetaField **enumStorage[] = { &k_cameraType, &k_horizontalFieldOfView, &k_nearPlane, &k_farPlane, &k_deadfield1, &k_deadfield2, &k_deadfield3 };
    static int offsets[] = { 28, 44, 48, 52, 32, 36, 40 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 7);
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->setDefault(0);
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())Gap::Sg::igCamera::getCameraTypeMetaEnum;
    }
    {
        igFloatMetaField *metaField = (igFloatMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->setDefault(45.0f);
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

static const char *g_igCamera_cameraTypeNames[] = {
    "CameraPoint", "CameraTarget",
};
static int g_igCamera_cameraTypeValues[] = {
    0, 1,
};
namespace Gap {
namespace Sg {

igMetaEnum *igCamera::CameraType_Meta;

igMetaEnum *igCamera::getCameraTypeMetaEnum() {
    if (CameraType_Meta == 0) {
        CameraType_Meta = Gap::Core::igMetaEnum::createMetaEnum("CameraType", g_igCamera_cameraTypeNames, g_igCamera_cameraTypeValues, 2);
    }
    return CameraType_Meta;
}
}
}

