namespace Gap {
namespace Viewer {

igMetaObject *igCameraMode::_Meta;
igMetaField *igCameraMode::k_cameraPath;
igMetaField *igCameraMode::k_camera;

igCameraMode *igCameraMode::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igCameraMode *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igCameraMode::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igCameraMode::retrieveVTablePointer()
{
    igCameraMode temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igCameraMode::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igCameraMode::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Sg::igGraphPath::arkRegister, Gap::Sg::igCamera::arkRegister, 0 };

    ViewerLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Viewer::igViewMode::arkRegisterInternal,
        Gap::Viewer::igViewMode::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igCameraMode",
        sizeof(igCameraMode),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igCameraMode::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create, igObjectRefMetaField_Create };
    static const char *names[] = { "_cameraPath", "_camera" };
    static igMetaField **enumStorage[] = { &k_cameraPath, &k_camera };
    static int offsets[] = { 76, 80 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 2);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)Gap::Sg::igGraphPath::getClassTypeLazy();
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->_metaObject = (int)Gap::Sg::igCamera::getClassTypeLazy();
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

