namespace Gap {
namespace Sg {

igTransform *igTransform::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igTransform *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igTransform::_Meta;
igMetaField *igTransform::k_m;
igMetaField *igTransform::k_target;
igMetaField *igTransform::k_mvm;
igMetaField *igTransform::k_transformInput;

igMetaObject *igTransform::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igTransform::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igTransform::retrieveVTablePointer()
{
    igTransform temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igTransform::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igTransform::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Attrs::igVisualAttribute::arkRegister, (igMetaObjectCallback)Gap::Sg::igTransformSource::arkRegister, 0 };

    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Sg::igGroup::arkRegisterInternal,
        Gap::Sg::igGroup::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igTransform",
        sizeof(igTransform),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igTransform::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { (FieldFactory)Gap::Math::igMatrix44fMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, igObjectRefMetaField_Create, igObjectRefMetaField_Create };
    static const char *names[] = { "_m", "_target", "_mvm", "_transformInput" };
    static igMetaField **enumStorage[] = { &k_m, &k_target, &k_mvm, &k_transformInput };
    static int offsets[] = { 32, 96, 100, 104 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 4);
    {
        igMatrix44fMetaField *metaField = (igMatrix44fMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->setDefault(igMatrix44f(igVec4f(1.0f, 0.0f, 0.0f, 0.0f), igVec4f(0.0f, 1.0f, 0.0f, 0.0f),
                                          igVec4f(0.0f, 0.0f, 1.0f, 0.0f), igVec4f(0.0f, 0.0f, 0.0f, 1.0f)));
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->setDefault(0);
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->_metaObject = (int)Gap::Attrs::igVisualAttribute::getClassTypeLazy();
        metaField->_persistent = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 3);
        metaField->_metaObject = (int)Gap::Sg::igTransformSource::getClassTypeLazy();
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

