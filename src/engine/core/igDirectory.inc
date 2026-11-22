namespace Gap {
namespace Core {

igDirectory *igDirectory::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igDirectory *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igDirectory::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igDirectory::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igDirectory::retrieveVTablePointer()
{
    igDirectory temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igDirectory::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igDirectory::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Core::igDirEntry::arkRegister, Gap::Core::igDirectoryList::arkRegister, Gap::Core::igInfoList::arkRegister, igResource_EnsureRegistered, igShortListList_EnsureRegistered, Gap::Core::igPointerList::arkRegister, Gap::Core::igSemaphore::arkRegister, 0 };

    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igDirectory",
        sizeof(igDirectory),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        (igMetaObjectCallback)Gap::Core::igDirectory::arkRegisterUser,
        regFunctions
    );
}

void igDirectory::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igStringMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igBoolMetaField_Create, igBoolMetaField_Create, igBoolMetaField_Create, igIntMetaField_Create, igObjectRefMetaField_Create, igBoolMetaField_Create, igBoolMetaField_Create, igBoolMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igBoolMetaField_Create, igBoolMetaField_Create, igBoolMetaField_Create, igObjectRefMetaField_Create };
    static const char *names[] = { "_name", "_externalDirectoryList", "_infoList", "_managingResource", "_loadPendingState", "_validState", "_compatibleState", "_loadedRefCount", "_metaFieldPerObjectIndices", "_concreteState", "_sharingState", "_trackUniqueEntries", "_uniqueEntryList", "_refList", "_autoWriteFilePreProcessState", "_useMemoryPoolAssignmentsState", "_forceWriteMemoryPoolInfoFromMetaState", "_loadingSemaphore" };
    static igMetaField **enumStorage[] = { &k_name, &k_externalDirectoryList, &k_infoList, &k_managingResource, &k_loadPendingState, &k_validState, &k_compatibleState, &k_loadedRefCount, &k_metaFieldPerObjectIndices, &k_concreteState, &k_sharingState, &k_trackUniqueEntries, &k_uniqueEntryList, &k_refList, &k_autoWriteFilePreProcessState, &k_useMemoryPoolAssignmentsState, &k_forceWriteMemoryPoolInfoFromMetaState, &k_loadingSemaphore };
    static int offsets[] = { 20, 24, 28, 32, 48, 49, 50, 52, 60, 56, 36, 37, 40, 44, 64, 65, 66, 68 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 18);
    {
        igStringMetaField *metaField = (igStringMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->setDefault(0);
        metaField->_destruct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->_metaObject = (int)Gap::Core::igDirectoryList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->_metaObject = (int)Gap::Core::igInfoList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 3);
        metaField->_metaObject = (int)igResource_GetOrCreateMetaObject();
        metaField->_refCounted = 0;
    }
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 5);
        metaField->setDefault(1);
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 8);
        metaField->_metaObject = (int)igShortListList_GetOrCreateMetaObject();
    }
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 10);
        metaField->setDefault(1);
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 12);
        metaField->_metaObject = (int)getClassTypeLazy();
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 13);
        metaField->_metaObject = (int)Gap::Core::igPointerList::getClassTypeLazy();
    }
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 14);
        metaField->setDefault(1);
    }
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 15);
        metaField->setDefault(1);
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 17);
        metaField->_metaObject = (int)Gap::Core::igSemaphore::getClassTypeLazy();
        metaField->_persistent = 0;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}

void igDirectory::arkRegisterUser() {
    userRegister();
}
}
}

