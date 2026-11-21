namespace Gap {
namespace Core {

igMetaObject *igRegistryValue::_Meta;
igMetaField *igRegistryValue::k_section;
igMetaField *igRegistryValue::k_value;
igMetaField *igRegistryValue::k_valueName;

igRegistryValue *igRegistryValue::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igRegistryValue *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igRegistryValue::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igRegistryValue::retrieveVTablePointer()
{
    igRegistryValue temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igRegistryValue::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igRegistryValue::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { igStringObj_EnsureRegistered, 0 };

    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igRegistryValue",
        sizeof(igRegistryValue),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igRegistryValue::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igIntMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create };
    static const char *names[] = { "_section", "_value", "_valueName" };
    static igMetaField **enumStorage[] = { &k_section, &k_value, &k_valueName };
    static int offsets[] = { 8, 12, 16 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 3);
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->setDefault(-1);
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->_metaObject = (int)igStringObj_GetOrCreateMetaObject();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->_metaObject = (int)igStringObj_GetOrCreateMetaObject();
        metaField->_construct = 1;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

