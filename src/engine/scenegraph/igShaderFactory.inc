static const char *g_igShaderFactory_fileCachingModeNames[] = {
    "NO_CACHING", "NON_PERSISTENT_CACHE", "PERSISTENT_CACHE", "GLOBAL_CACHE",
};
static int g_igShaderFactory_fileCachingModeValues[] = {
    0, 1, 2, 3,
};
namespace Gap {
namespace Sg {

igMetaEnum *igShaderFactory::FILE_CACHING_MODE_Meta;

igMetaEnum *igShaderFactory::getFILE_CACHING_MODEMetaEnum()
{
    if (FILE_CACHING_MODE_Meta == 0) {
        FILE_CACHING_MODE_Meta = igMetaEnum::createMetaEnum("FILE_CACHING_MODE", g_igShaderFactory_fileCachingModeNames, g_igShaderFactory_fileCachingModeValues, 4);
    }
    return FILE_CACHING_MODE_Meta;
}

igMetaObject *igShaderFactory::_Meta;
igMetaField *igShaderFactory::k_attrNames;
igMetaField *igShaderFactory::k_attrTypes;
igMetaField *igShaderFactory::k_fileCachingMode;

igMetaObject *igShaderFactory::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igShaderFactory::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igShaderFactory::retrieveVTablePointer()
{
    igShaderFactory temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}
}
}

igSmartPointer<igObject> *igSmartPointer_igNamedObjectList_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        igObject::release(object);
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

namespace Gap {
namespace Sg {

void igShaderFactory::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igShaderFactory::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { igNamedObjectList_EnsureRegistered, 0 };

    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igNamedObject::arkRegisterInternal,
        Gap::Core::igNamedObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igShaderFactory",
        sizeof(igShaderFactory),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igShaderFactory::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create, igObjectRefMetaField_Create, igEnumMetaField_Create };
    static const char *names[] = { "_attrNames", "_attrTypes", "_fileCachingMode" };
    static igMetaField **enumStorage[] = { &k_attrNames, &k_attrTypes, &k_fileCachingMode };
    static int offsets[] = { 12, 16, 20 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 3);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)igNamedObjectList_GetOrCreateMetaObject();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->_metaObject = (int)igNamedObjectList_GetOrCreateMetaObject();
        metaField->_construct = 1;
    }
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->setDefault(3);
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())Gap::Sg::igShaderFactory::getFILE_CACHING_MODEMetaEnum;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

