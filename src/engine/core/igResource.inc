namespace Gap {
namespace Core {

igMetaObject *igResource::_Meta;
igMetaField *igResource::k_imageDirectory;
igMetaField *igResource::k_directoryList;
igMetaField *igResource::k_relativeFilePath;
igMetaField *igResource::k_absoluteFilePath;
igMetaField *igResource::k_asyncLoadState;
igMetaField *igResource::k_loadQueue;
igMetaField *igResource::k_loadThread;
igMetaField *igResource::k_autoCompatibility;
igMetaField *igResource::k_alignmentStrings;
igMetaField *igResource::k_alignmentValues;
igMetaField *igResource::k_postProcessAsyncronousFilesState;
igMetaField *igResource::k_temporaryMemoryPool;
igMetaField *igResource::k_dataMemoryPool;
igMetaField *igResource::k_objectMemoryPool;
igMetaField *igResource::k_IGBSharingState;
igMetaField *igResource::k_IGBChunkSize;
igMetaField *igResource::k_useMemoryPoolAssignmentsState;

igResource *igResource::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igResource *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igResource::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igResource::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igResource::retrieveVTablePointer()
{
    igResource temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igResource::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igResource::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Core::igDirectory::arkRegister, Gap::Core::igDirectoryList::arkRegister, igQueue_EnsureRegistered, igThread_EnsureRegistered, igStringObjList_EnsureRegistered, Gap::Core::igIntList::arkRegister, igMemoryPool_EnsureRegistered, 0 };

    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igResource",
        sizeof(igResource),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igResource::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create, igObjectRefMetaField_Create, igStringMetaField_Create, igStringMetaField_Create, igBoolMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igBoolMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igBoolMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igBoolMetaField_Create, igIntMetaField_Create, igBoolMetaField_Create };
    static const char *names[] = { "_imageDirectory", "_directoryList", "_relativeFilePath", "_absoluteFilePath", "_asyncLoadState", "_loadQueue", "_loadThread", "_autoCompatibility", "_alignmentStrings", "_alignmentValues", "_postProcessAsyncronousFilesState", "_temporaryMemoryPool", "_dataMemoryPool", "_objectMemoryPool", "_IGBSharingState", "_IGBChunkSize", "_useMemoryPoolAssignmentsState" };
    static igMetaField **enumStorage[] = { &k_imageDirectory, &k_directoryList, &k_relativeFilePath, &k_absoluteFilePath, &k_asyncLoadState, &k_loadQueue, &k_loadThread, &k_autoCompatibility, &k_alignmentStrings, &k_alignmentValues, &k_postProcessAsyncronousFilesState, &k_temporaryMemoryPool, &k_dataMemoryPool, &k_objectMemoryPool, &k_IGBSharingState, &k_IGBChunkSize, &k_useMemoryPoolAssignmentsState };
    static int offsets[] = { 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60, 64, 68, 72, 8 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 17);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)Gap::Core::igDirectory::getClassTypeLazy();
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->_metaObject = (int)Gap::Core::igDirectoryList::getClassTypeLazy();
        metaField->_construct = 1;
        metaField->_persistent = 0;
    }
    {
        igStringMetaField *metaField = (igStringMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->setDefault(0);
    }
    {
        igStringMetaField *metaField = (igStringMetaField *)igMetaObject_GetFieldAt(metaObject, start + 3);
        metaField->setDefault(0);
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 5);
        metaField->_metaObject = (int)igQueue_GetOrCreateMetaObject();
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 6);
        metaField->_metaObject = (int)igThread_GetOrCreateMetaObject();
    }
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 7);
        metaField->setDefault(1);
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 8);
        metaField->_metaObject = (int)igStringObjList_GetOrCreateMetaObject();
        metaField->_persistent = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 9);
        metaField->_metaObject = (int)Gap::Core::igIntList::getClassTypeLazy();
        metaField->_persistent = 0;
    }
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 10);
        metaField->setDefault(1);
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 11);
        metaField->_metaObject = (int)igMemoryPool_GetOrCreateMetaObject();
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 12);
        metaField->_metaObject = (int)igMemoryPool_GetOrCreateMetaObject();
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 13);
        metaField->_metaObject = (int)igMemoryPool_GetOrCreateMetaObject();
    }
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 14);
        metaField->setDefault(1);
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 15);
        metaField->setDefault(131072);
    }
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 16);
        metaField->setDefault(1);
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

