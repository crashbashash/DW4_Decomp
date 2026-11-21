namespace Gap {
namespace Core {

igMetaObject *igExternalIndexedEntry::_Meta;
igMetaField *igExternalIndexedEntry::k_directoryIndex;
igMetaField *igExternalIndexedEntry::k_entryIndex;
igMetaField *igExternalIndexedEntry::k_entryType;
igMetaField *igExternalIndexedEntry::k_entryTypeIndex;
igMetaField *igExternalIndexedEntry::k_objectType;
igMetaField *igExternalIndexedEntry::k_objectTypeIndex;

igMetaObject *igExternalIndexedEntry::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igExternalIndexedEntry::retrieveVTablePointer()
{
    igExternalIndexedEntry temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igExternalIndexedEntry::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igExternalIndexedEntry::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { igMetaObject_EnsureRegistered, 0 };

    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igDirEntry::arkRegisterInternal,
        Gap::Core::igDirEntry::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igExternalIndexedEntry",
        sizeof(igExternalIndexedEntry),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igExternalIndexedEntry::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igIntMetaField_Create, igIntMetaField_Create, igObjectRefMetaField_Create, igIntMetaField_Create, igObjectRefMetaField_Create, igIntMetaField_Create };
    static const char *names[] = { "_directoryIndex", "_entryIndex", "_entryType", "_entryTypeIndex", "_objectType", "_objectTypeIndex" };
    static igMetaField **enumStorage[] = { &k_directoryIndex, &k_entryIndex, &k_entryType, &k_entryTypeIndex, &k_objectType, &k_objectTypeIndex };
    static int offsets[] = { 28, 32, 36, 40, 44, 48 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 6);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->_metaObject = (int)igMetaObject_GetOrCreateMetaObject();
        metaField->_persistent = 0;
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 3);
        metaField->setDefault(-1);
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 4);
        metaField->_metaObject = (int)igMetaObject_GetOrCreateMetaObject();
        metaField->_persistent = 0;
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 5);
        metaField->setDefault(-1);
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

