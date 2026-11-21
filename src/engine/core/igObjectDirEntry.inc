namespace Gap {
namespace Core {

igMetaObject *igObjectDirEntry::_Meta;
igMetaField *igObjectDirEntry::k_typeMeta;
igMetaField *igObjectDirEntry::k_typeMetaName;
igMetaField *igObjectDirEntry::k_majorVersion;
igMetaField *igObjectDirEntry::k_minorVersion;
igMetaField *igObjectDirEntry::k_ref;
igMetaField *igObjectDirEntry::k_typeMetaIndex;
igMetaField *igObjectDirEntry::k_memoryPoolHandle;

igObjectDirEntry *igObjectDirEntry::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igObjectDirEntry *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igObjectDirEntry::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igObjectDirEntry::retrieveVTablePointer()
{
    igObjectDirEntry temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igObjectDirEntry::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igObjectDirEntry::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { igMetaObject_EnsureRegistered, Gap::Core::igObject::arkRegister, 0 };

    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igDirEntry::arkRegisterInternal,
        Gap::Core::igDirEntry::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igObjectDirEntry",
        sizeof(igObjectDirEntry),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

igMetaObject *igDirEntry::_Meta;
igMetaField *igDirEntry::k_index;
igMetaField *igDirEntry::k_resolveMethod;
igMetaField *igDirEntry::k_refType;
igMetaField *igDirEntry::k_ref;

igMetaObject *igObject::_Meta;

void igObjectDirEntry::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create, igStringMetaField_Create, igIntMetaField_Create, igIntMetaField_Create, igIntMetaField_Create, igIntMetaField_Create };
    static const char *names[] = { "_typeMeta", "_typeMetaName", "_majorVersion", "_minorVersion", "_typeMetaIndex", "_memoryPoolHandle" };
    static igMetaField **enumStorage[] = { &k_typeMeta, &k_typeMetaName, &k_majorVersion, &k_minorVersion, &k_typeMetaIndex, &k_memoryPoolHandle };
    static int offsets[] = { 28, 32, 36, 40, 48, 44 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 6);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)igMetaObject_GetOrCreateMetaObject();
        metaField->_persistent = 0;
    }
    {
        igStringMetaField *metaField = (igStringMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->setDefault("NoMeta");
        metaField->_destruct = 1;
        metaField->_persistent = 0;
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->_persistent = 0;
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 3);
        metaField->_persistent = 0;
    }
    {
        __internalNonRefCountedObjectList *metaFields = (__internalNonRefCountedObjectList *)metaObject->_metaFields;
        int metaIndex = ObjectPointerList_FindIndex(metaFields, (int)igMetaObject_FindFieldByName(metaObject, "_ref"));
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igObjectRefMetaField_Create(Memory_GetAllocatorBySelector((int)kIGMemoryPoolHandleMetaData));
        metaField->setBasicProperties("_ref", &k_ref, 24, metaObject);
        metaField->_metaObject = (int)Gap::Core::igObject::getClassMeta();
        metaField->setDefault(0);
        metaField->_persistent = 0;
        metaField->_externalEnumStorage = (int)&k_ref;
        igMetaObject_FinalizeAndReplaceField(metaObject, metaIndex, (::igMetaField *)metaField);
        metaField->release();
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 4);
        metaField->setDefault(-1);
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 5);
        metaField->setDefault(-1);
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

