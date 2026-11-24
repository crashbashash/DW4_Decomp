namespace Gap {
namespace Sg {

igMetaObject *igIniShaderFactory::_Meta;
igMetaField *igIniShaderFactory::k_implementationName;
igMetaField *igIniShaderFactory::k_fileCache;
igMetaField *igIniShaderFactory::k_implementation;
igMetaField *igIniShaderFactory::k_interface;
igMetaField *igIniShaderFactory::k_interfaceFileName;
igMetaField *igIniShaderFactory::k_interfaceSection;
igMetaField *igIniShaderFactory::k_mp;
igMetaField *igIniShaderFactory::k_data;
igMetaField *igIniShaderFactory::k_cachedObjects;

igMetaObject *igIniShaderFactory::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igIniShaderFactory::retrieveVTablePointer()
{
    igIniShaderFactory temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}
}
}

namespace Gap {
namespace Sg {

void igIniShaderFactory::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igIniShaderFactory::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { igObjectStringMap_EnsureRegistered, Gap::Core::igRegistry::arkRegister, igMemoryPool_EnsureRegistered, Gap::Sg::igInterpretedShaderData::arkRegister, 0 };

    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Sg::igShaderFactory::arkRegisterInternal,
        Gap::Sg::igShaderFactory::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igIniShaderFactory",
        sizeof(igIniShaderFactory),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igIniShaderFactory::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igStringMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igStringMetaField_Create, igIntMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create };
    static const char *names[] = { "_implementationName", "_fileCache", "_implementation", "_interface", "_interfaceFileName", "_interfaceSection", "_mp", "_data", "_cachedObjects" };
    static igMetaField **enumStorage[] = { &k_implementationName, &k_fileCache, &k_implementation, &k_interface, &k_interfaceFileName, &k_interfaceSection, &k_mp, &k_data, &k_cachedObjects };
    static int offsets[] = { 24, 56, 28, 32, 36, 40, 44, 48, 52 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 9);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->_metaObject = (int)igObjectStringMap_GetOrCreateMetaObject();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->_metaObject = (int)Gap::Core::igRegistry::getClassTypeLazy();
        metaField->_persistent = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 3);
        metaField->_metaObject = (int)Gap::Core::igRegistry::getClassTypeLazy();
        metaField->_persistent = 0;
    }
    {
        igStringMetaField *metaField = (igStringMetaField *)igMetaObject_GetFieldAt(metaObject, start + 4);
        metaField->setDefault(0);
        metaField->_persistent = 0;
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 5);
        metaField->setDefault(-1);
        metaField->_persistent = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 6);
        metaField->_metaObject = (int)igMemoryPool_GetOrCreateMetaObject();
        metaField->_persistent = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 7);
        metaField->_metaObject = (int)Gap::Sg::igInterpretedShaderData::getClassTypeLazy();
        metaField->_persistent = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 8);
        metaField->_metaObject = (int)igObjectStringMap_GetOrCreateMetaObject();
        metaField->_construct = 1;
        metaField->_persistent = 0;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

