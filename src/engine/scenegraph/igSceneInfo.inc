namespace Gap {
namespace Sg {

igSceneInfo *igSceneInfo::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igSceneInfo *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igSceneInfo::_Meta;
igMetaField *igSceneInfo::k_sceneGraph;
igMetaField *igSceneInfo::k_textures;
igMetaField *igSceneInfo::k_cameras;
igMetaField *igSceneInfo::k_animationBegin;
igMetaField *igSceneInfo::k_animationEnd;
igMetaField *igSceneInfo::k_upVector;
igMetaField *igSceneInfo::k_sceneGraphList;

igMetaObject *igSceneInfo::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igSceneInfo::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igSceneInfo::retrieveVTablePointer()
{
    igSceneInfo temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igSceneInfo::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igSceneInfo::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Sg::igNode::arkRegister, Gap::Attrs::igTextureList::arkRegister, Gap::Sg::igGraphPathList::arkRegister, Gap::Sg::igNodeList::arkRegister, 0 };

    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igInfo::arkRegisterInternal,
        Gap::Core::igInfo::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igSceneInfo",
        sizeof(igSceneInfo),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igSceneInfo::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, (FieldFactory)Gap::Core::igLongMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igLongMetaField::_instantiateFromPool, (FieldFactory)Gap::Math::igVec3fMetaField::_instantiateFromPool, igObjectRefMetaField_Create };
    static const char *names[] = { "_sceneGraph", "_textures", "_cameras", "_animationBegin", "_animationEnd", "_upVector", "_sceneGraphList" };
    static igMetaField **enumStorage[] = { &k_sceneGraph, &k_textures, &k_cameras, &k_animationBegin, &k_animationEnd, &k_upVector, &k_sceneGraphList };
    static int offsets[] = { 20, 24, 28, 32, 40, 48, 60 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 7);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)Gap::Sg::igNode::getClassTypeLazy();
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->_metaObject = (int)Gap::Attrs::igTextureList::getClassTypeLazy();
        metaField->_construct = 1;
        metaField->_deepCopyMethod = 0;
        metaField->_shallowCopyMethod = 2;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->_metaObject = (int)Gap::Sg::igGraphPathList::getClassTypeLazy();
        metaField->_construct = 1;
        metaField->_deepCopyMethod = 0;
        metaField->_shallowCopyMethod = 2;
    }
    {
        igVec3fMetaField *metaField = (igVec3fMetaField *)igMetaObject_GetFieldAt(metaObject, start + 5);
        metaField->setDefault(igVec3f(0.0f, 1.0f, 0.0f));
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 6);
        metaField->_metaObject = (int)Gap::Sg::igNodeList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

