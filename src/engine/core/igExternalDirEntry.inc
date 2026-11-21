namespace Gap {
namespace Core {

igMetaObject *igExternalDirEntry::_Meta;
igMetaField *igExternalDirEntry::k_ref;
igMetaField *igExternalDirEntry::k_directoryName;
igMetaField *igExternalDirEntry::k_entryName;
igMetaField *igExternalDirEntry::k_entryIndex;
igMetaField *igExternalDirEntry::k_externalFilePath;

igMetaObject *igExternalDirEntry::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igExternalDirEntry::retrieveVTablePointer()
{
    igExternalDirEntry temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igExternalDirEntry::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igExternalDirEntry::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Core::igObject::arkRegister, 0 };

    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igDirEntry::arkRegisterInternal,
        Gap::Core::igDirEntry::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igExternalDirEntry",
        sizeof(igExternalDirEntry),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igExternalDirEntry::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igStringMetaField_Create, igStringMetaField_Create, igIntMetaField_Create, igStringMetaField_Create };
    static const char *names[] = { "_directoryName", "_entryName", "_entryIndex", "_externalFilePath" };
    static igMetaField **enumStorage[] = { &k_directoryName, &k_entryName, &k_entryIndex, &k_externalFilePath };
    static int offsets[] = { 28, 32, 36, 40 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 4);
    {
        __internalNonRefCountedObjectList *metaFields = (__internalNonRefCountedObjectList *)metaObject->_metaFields;
        int metaIndex = metaFields->find((igObject *)igMetaObject_FindFieldByName(metaObject, "_ref"));
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igObjectRefMetaField_Create(Memory_GetAllocatorBySelector((int)kIGMemoryPoolHandleMetaData));
        metaField->setBasicProperties("_ref", &k_ref, 24, metaObject);
        metaField->_metaObject = (int)Gap::Core::igObject::getClassMeta();
        metaField->_persistent = 0;
        metaField->_externalEnumStorage = (int)&k_ref;
        igMetaObject_FinalizeAndReplaceField(metaObject, metaIndex, (::igMetaField *)metaField);
        metaField->release();
    }
    {
        igStringMetaField *metaField = (igStringMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->setDefault("Intrinsic");
    }
    {
        igStringMetaField *metaField = (igStringMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->setDefault("default");
    }
    {
        igStringMetaField *metaField = (igStringMetaField *)igMetaObject_GetFieldAt(metaObject, start + 3);
        metaField->setDefault("");
        metaField->_persistent = 0;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

