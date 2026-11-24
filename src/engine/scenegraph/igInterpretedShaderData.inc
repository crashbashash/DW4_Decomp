namespace Gap {
namespace Sg {

igMetaObject *igInterpretedShaderData::_Meta;
igMetaField *igInterpretedShaderData::k_factory;
igMetaField *igInterpretedShaderData::k_objectMappings;

igMetaObject *igInterpretedShaderData::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igInterpretedShaderData::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igInterpretedShaderData::retrieveVTablePointer()
{
    igInterpretedShaderData temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}
}
}

namespace Gap {
namespace Sg {

void igInterpretedShaderData::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igInterpretedShaderData::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Sg::igShaderFactory::arkRegister, igObjectStringMap_EnsureRegistered, 0 };

    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Sg::igTransientShaderData::arkRegisterInternal,
        Gap::Sg::igTransientShaderData::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igInterpretedShaderData",
        sizeof(igInterpretedShaderData),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}
}
}

namespace Gap {
namespace Sg {

void igInterpretedShaderData::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create, igObjectRefMetaField_Create };
    static const char *names[] = { "_factory", "_objectMappings" };
    static igMetaField **enumStorage[] = { &k_factory, &k_objectMappings };
    static int offsets[] = { 24, 28 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 2);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)Gap::Sg::igShaderFactory::getClassTypeLazy();
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->_metaObject = (int)igObjectStringMap_GetOrCreateMetaObject();
        metaField->_construct = 1;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

