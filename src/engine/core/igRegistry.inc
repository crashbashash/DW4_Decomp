namespace Gap {
namespace Core {

igMetaObject *igRegistry::_Meta;
igMetaField *igRegistry::k_valueTable;
igMetaField *igRegistry::k_registryFile;
igMetaField *igRegistry::k_additionalSectionNames;
igMetaField *igRegistry::k_showQueries;
igMetaField *igRegistry::k_valueNameCaseSensitive;

igRegistry *igRegistry::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igRegistry *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igRegistry::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igRegistry::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igRegistry::retrieveVTablePointer()
{
    igRegistry temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igRegistry::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igRegistry::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Core::igRegistryValueList::arkRegister, Gap::Core::igFile::arkRegister, igStringObjList_EnsureRegistered, 0 };

    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igRegistry",
        sizeof(igRegistry),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igRegistry::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igBoolMetaField_Create, igBoolMetaField_Create };
    static const char *names[] = { "_valueTable", "_registryFile", "_additionalSectionNames", "_showQueries", "_valueNameCaseSensitive" };
    static igMetaField **enumStorage[] = { &k_valueTable, &k_registryFile, &k_additionalSectionNames, &k_showQueries, &k_valueNameCaseSensitive };
    static int offsets[] = { 8, 12, 16, 20, 21 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 5);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)Gap::Core::igRegistryValueList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->_metaObject = (int)Gap::Core::igFile::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->_metaObject = (int)igStringObjList_GetOrCreateMetaObject();
        metaField->_construct = 1;
    }
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 4);
        metaField->setDefault(1);
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

