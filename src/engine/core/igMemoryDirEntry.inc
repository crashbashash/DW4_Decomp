namespace Gap {
namespace Core {

igMetaObject *igMemoryDirEntry::_Meta;
igMetaField *igMemoryDirEntry::k_memSize;
igMetaField *igMemoryDirEntry::k_memTypeSize;
igMetaField *igMemoryDirEntry::k_memType;
igMetaField *igMemoryDirEntry::k_memTypeIndex;
igMetaField *igMemoryDirEntry::k_refCounted;
igMetaField *igMemoryDirEntry::k_alignmentTypeIndex;
igMetaField *igMemoryDirEntry::k_memoryPoolHandle;

igMemoryDirEntry *igMemoryDirEntry::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igMemoryDirEntry *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igMemoryDirEntry::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igMemoryDirEntry::retrieveVTablePointer()
{
    igMemoryDirEntry temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igMemoryDirEntry::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igMemoryDirEntry::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Core::igMetaField::arkRegister, 0 };

    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igDirEntry::arkRegisterInternal,
        Gap::Core::igDirEntry::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igMemoryDirEntry",
        sizeof(igMemoryDirEntry),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igMemoryDirEntry::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igIntMetaField_Create, igIntMetaField_Create, igObjectRefMetaField_Create, igIntMetaField_Create, igBoolMetaField_Create, igIntMetaField_Create, igIntMetaField_Create };
    static const char *names[] = { "_memSize", "_memTypeSize", "_memType", "_memTypeIndex", "_refCounted", "_alignmentTypeIndex", "_memoryPoolHandle" };
    static igMetaField **enumStorage[] = { &k_memSize, &k_memTypeSize, &k_memType, &k_memTypeIndex, &k_refCounted, &k_alignmentTypeIndex, &k_memoryPoolHandle };
    static int offsets[] = { 28, 32, 36, 40, 52, 44, 48 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 7);
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->setDefault(-1);
        metaField->_persistent = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->_metaObject = (int)Gap::Core::igMetaField::getClassTypeLazy();
        metaField->setDefault((igObject *)Gap::Core::igCharMetaField::getMetaField());
        metaField->_refCounted = 0;
        metaField->_persistent = 0;
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 3);
        metaField->setDefault(-1);
    }
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 4);
        metaField->setDefault(1);
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 5);
        metaField->setDefault(-1);
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 6);
        metaField->setDefault(-1);
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

