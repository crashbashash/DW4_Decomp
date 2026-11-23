namespace Gap {
namespace Core {

igMetaObject *igIGBFile::_Meta;
igMetaField *igIGBFile::k_data;
igMetaField *igIGBFile::k_count;
igMetaField *igIGBFile::k_capacity;
igMetaField *igIGBFile::k_magicCookie;
igMetaField *igIGBFile::k_magicVersion;
igMetaField *igIGBFile::k_file;
igMetaField *igIGBFile::k_majorVersion;
igMetaField *igIGBFile::k_minorVersion;
igMetaField *igIGBFile::k_hasTemplates;
igMetaField *igIGBFile::k_entryCount;
igMetaField *igIGBFile::k_indexBufferSize;
igMetaField *igIGBFile::k_indexBuffer;
igMetaField *igIGBFile::k_entryBufferSize;
igMetaField *igIGBFile::k_metaObjectCount;
igMetaField *igIGBFile::k_metaObjectBufferSize;
igMetaField *igIGBFile::k_metaFieldCount;
igMetaField *igIGBFile::k_metaFieldBufferSize;
igMetaField *igIGBFile::k_objectCount;
igMetaField *igIGBFile::k_objectBufferSize;
igMetaField *igIGBFile::k_memoryRefCount;
igMetaField *igIGBFile::k_memoryRefBufferSize;
igMetaField *igIGBFile::k_userLoadFunction;
igMetaField *igIGBFile::k_forceChunkSize;
igMetaField *igIGBFile::k_endianSwap;
igMetaField *igIGBFile::k_metaObjectBuffer;
igMetaField *igIGBFile::k_dirBuf;
igMetaField *igIGBFile::k_objBuf;
igMetaField *igIGBFile::k_mfBuf;
igMetaField *igIGBFile::k_metaFieldListInFile;
igMetaField *igIGBFile::k_metaObjectListInFile;
igMetaField *igIGBFile::k_autoOpened;
igMetaField *igIGBFile::k_basePath;
igMetaField *igIGBFile::k_imf;
igMetaField *igIGBFile::k_smf;
igMetaField *igIGBFile::k_hasInfo;
igMetaField *igIGBFile::k_hasExternal;
igMetaField *igIGBFile::k_sharedEntries;
igMetaField *igIGBFile::k_hasVersion1Cruft;
igMetaField *igIGBFile::k_version1CruftMultiply;
igMetaField *igIGBFile::k_infoListPlace;
igMetaField *igIGBFile::k_externalDirectoryBuffer;
igMetaField *igIGBFile::k_externalDirectoryBufferSize;
igMetaField *igIGBFile::k_previousResourceFilePath;
igMetaField *igIGBFile::k_alignmentBuffer;
igMetaField *igIGBFile::k_alignmentBufferSize;
igMetaField *igIGBFile::k_alignmentListInFile;
igMetaField *igIGBFile::k_alignmentCount;
igMetaField *igIGBFile::k_objectBufferPlace;
igMetaField *igIGBFile::k_memoryBufferPlace;
igMetaField *igIGBFile::k_chunkSize;
igMetaField *igIGBFile::k_chunk;
igMetaField *igIGBFile::k_chunkPlace;
igMetaField *igIGBFile::k_bufferPlace;
igMetaField *igIGBFile::k_bufferSize;
igMetaField *igIGBFile::k_memoryBytesCopied;
igMetaField *igIGBFile::k_bytesRemainingInChunk;
igMetaField *igIGBFile::k_hasCriticalFailure;
igMetaField *igIGBFile::k_autoReadFilePostProcessState;
igMetaField *igIGBFile::k_autoWriteFilePostProcessState;
igMetaField *igIGBFile::k_readFilePostProcessedState;
igMetaField *igIGBFile::k_temporaryMemoryPool;
igMetaField *igIGBFile::k_dataMemoryPool;
igMetaField *igIGBFile::k_objectMemoryPool;
igMetaField *igIGBFile::k_entryPool;
igMetaField *igIGBFile::k_hasMemoryPoolNames;
igMetaField *igIGBFile::k_memoryPoolNameBufferSize;
igMetaField *igIGBFile::k_memoryPoolNameBuffer;
igMetaField *igIGBFile::k_memoryPoolHandles;

igIGBFile *igIGBFile::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igIGBFile *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igIGBFile::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igIGBFile::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igIGBFile::retrieveVTablePointer()
{
    igIGBFile temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}
void igIGBFile::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igIGBFile::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Core::igFile::arkRegister, igMetaFieldList_EnsureRegistered, igMetaObjectList_EnsureRegistered, Gap::Core::igMetaField::arkRegister, Gap::Core::igIntList::arkRegister, igMemoryPool_EnsureRegistered, Gap::Core::igObjectList::arkRegister, 0 };

    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igDirectory::arkRegisterInternal,
        Gap::Core::igDirectory::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igIGBFile",
        sizeof(igIGBFile),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        (igMetaObjectCallback)Gap::Core::igIGBFile::arkRegisterUser,
        regFunctions
    );
}

igMetaObject *igDirectory::_Meta;
igMetaField *igDirectory::k_name;
igMetaField *igDirectory::k_externalDirectoryList;
igMetaField *igDirectory::k_infoList;
igMetaField *igDirectory::k_managingResource;
igMetaField *igDirectory::k_loadPendingState;
igMetaField *igDirectory::k_validState;
igMetaField *igDirectory::k_compatibleState;
igMetaField *igDirectory::k_loadedRefCount;
igMetaField *igDirectory::k_metaFieldPerObjectIndices;
igMetaField *igDirectory::k_concreteState;
igMetaField *igDirectory::k_sharingState;
igMetaField *igDirectory::k_trackUniqueEntries;
igMetaField *igDirectory::k_uniqueEntryList;
igMetaField *igDirectory::k_refList;
igMetaField *igDirectory::k_autoWriteFilePreProcessState;
igMetaField *igDirectory::k_useMemoryPoolAssignmentsState;
igMetaField *igDirectory::k_forceWriteMemoryPoolInfoFromMetaState;
igMetaField *igDirectory::k_loadingSemaphore;

igMetaEnum *igDirEntry::RefType_Meta;
igMetaEnum *igDirEntry::ResolveMethod_Meta;

void igIGBFile::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igIntMetaField_Create, igIntMetaField_Create, igObjectRefMetaField_Create, igIntMetaField_Create, igIntMetaField_Create, igBoolMetaField_Create, igIntMetaField_Create, igIntMetaField_Create, igMemoryRefMetaField_Create, igIntMetaField_Create, igIntMetaField_Create, igIntMetaField_Create, igIntMetaField_Create, igIntMetaField_Create, igIntMetaField_Create, igIntMetaField_Create, igIntMetaField_Create, igIntMetaField_Create, igRawRefMetaField_Create, igIntMetaField_Create, igBoolMetaField_Create, igMemoryRefMetaField_Create, igMemoryRefMetaField_Create, igMemoryRefMetaField_Create, igMemoryRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igIntMetaField_Create, igMemoryRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igBoolMetaField_Create, igBoolMetaField_Create, igBoolMetaField_Create, igBoolMetaField_Create, igIntMetaField_Create, igIntMetaField_Create, igMemoryRefMetaField_Create, igIntMetaField_Create, igStringMetaField_Create, igMemoryRefMetaField_Create, igIntMetaField_Create, igObjectRefMetaField_Create, igIntMetaField_Create, igMemoryRefMetaField_Create, igIntMetaField_Create, igIntMetaField_Create, igMemoryRefMetaField_Create, igIntMetaField_Create, igIntMetaField_Create, igIntMetaField_Create, igIntMetaField_Create, igIntMetaField_Create, igBoolMetaField_Create, igBoolMetaField_Create, igBoolMetaField_Create, igBoolMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igBoolMetaField_Create, igIntMetaField_Create, igMemoryRefMetaField_Create, igObjectRefMetaField_Create };
    static const char *names[] = { "_magicCookie", "_magicVersion", "_file", "_majorVersion", "_minorVersion", "_hasTemplates", "_entryCount", "_indexBufferSize", "_indexBuffer", "_entryBufferSize", "_metaObjectCount", "_metaObjectBufferSize", "_metaFieldCount", "_metaFieldBufferSize", "_objectCount", "_objectBufferSize", "_memoryRefCount", "_memoryRefBufferSize", "_userLoadFunction", "_forceChunkSize", "_endianSwap", "_metaObjectBuffer", "_dirBuf", "_objBuf", "_mfBuf", "_metaFieldListInFile", "_metaObjectListInFile", "_autoOpened", "_basePath", "imf", "smf", "_hasInfo", "_hasExternal", "_sharedEntries", "_hasVersion1Cruft", "_version1CruftMultiply", "_infoListPlace", "_externalDirectoryBuffer", "_externalDirectoryBufferSize", "_previousResourceFilePath", "_alignmentBuffer", "_alignmentBufferSize", "_alignmentListInFile", "_alignmentCount", "_objectBufferPlace", "_memoryBufferPlace", "_chunkSize", "_chunk", "_chunkPlace", "_bufferPlace", "_bufferSize", "_memoryBytesCopied", "_bytesRemainingInChunk", "_hasCriticalFailure", "_autoReadFilePostProcessState", "_autoWriteFilePostProcessState", "_readFilePostProcessedState", "_temporaryMemoryPool", "_dataMemoryPool", "_objectMemoryPool", "_entryPool", "_hasMemoryPoolNames", "_memoryPoolNameBufferSize", "_memoryPoolNameBuffer", "_memoryPoolHandles" };
    static igMetaField **enumStorage[] = { &k_magicCookie, &k_magicVersion, &k_file, &k_majorVersion, &k_minorVersion, &k_hasTemplates, &k_entryCount, &k_indexBufferSize, &k_indexBuffer, &k_entryBufferSize, &k_metaObjectCount, &k_metaObjectBufferSize, &k_metaFieldCount, &k_metaFieldBufferSize, &k_objectCount, &k_objectBufferSize, &k_memoryRefCount, &k_memoryRefBufferSize, &k_userLoadFunction, &k_forceChunkSize, &k_endianSwap, &k_metaObjectBuffer, &k_dirBuf, &k_objBuf, &k_mfBuf, &k_metaFieldListInFile, &k_metaObjectListInFile, &k_autoOpened, &k_basePath, &k_imf, &k_smf, &k_hasInfo, &k_hasExternal, &k_sharedEntries, &k_hasVersion1Cruft, &k_version1CruftMultiply, &k_infoListPlace, &k_externalDirectoryBuffer, &k_externalDirectoryBufferSize, &k_previousResourceFilePath, &k_alignmentBuffer, &k_alignmentBufferSize, &k_alignmentListInFile, &k_alignmentCount, &k_objectBufferPlace, &k_memoryBufferPlace, &k_chunkSize, &k_chunk, &k_chunkPlace, &k_bufferPlace, &k_bufferSize, &k_memoryBytesCopied, &k_bytesRemainingInChunk, &k_hasCriticalFailure, &k_autoReadFilePostProcessState, &k_autoWriteFilePostProcessState, &k_readFilePostProcessedState, &k_temporaryMemoryPool, &k_dataMemoryPool, &k_objectMemoryPool, &k_entryPool, &k_hasMemoryPoolNames, &k_memoryPoolNameBufferSize, &k_memoryPoolNameBuffer, &k_memoryPoolHandles };
    static int offsets[] = { 96, 100, 104, 72, 76, 108, 112, 116, 120, 124, 128, 132, 136, 140, 144, 148, 152, 156, 160, 164, 168, 172, 176, 180, 184, 188, 192, 196, 200, 204, 208, 212, 213, 214, 215, 216, 220, 224, 228, 232, 236, 240, 244, 248, 252, 256, 260, 264, 80, 84, 88, 268, 272, 276, 277, 278, 279, 280, 284, 288, 92, 292, 296, 300, 304 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 65);
    {
        igMemoryRefMetaField *metaField = (igMemoryRefMetaField *)igMetaObject_FindFieldByName(metaObject, "_data");
        int metaIndex = ((__internalNonRefCountedObjectList *)metaObject->_metaFields)->find(metaField);
        metaField = (igMemoryRefMetaField *)((igObjectDispatchView *)metaField)->CloneViaMetadata(1);
        metaField->_persistent = 0;
        metaField->_externalEnumStorage = (int)&k_data;
        igMetaObject_FinalizeAndReplaceField(metaObject, metaIndex, (::igMetaField *)metaField);
        metaField->release();
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_FindFieldByName(metaObject, "_count");
        int metaIndex = ((__internalNonRefCountedObjectList *)metaObject->_metaFields)->find(metaField);
        metaField = (igIntMetaField *)((igObjectDispatchView *)metaField)->CloneViaMetadata(1);
        metaField->_persistent = 0;
        metaField->_externalEnumStorage = (int)&k_count;
        igMetaObject_FinalizeAndReplaceField(metaObject, metaIndex, (::igMetaField *)metaField);
        metaField->release();
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_FindFieldByName(metaObject, "_capacity");
        int metaIndex = ((__internalNonRefCountedObjectList *)metaObject->_metaFields)->find(metaField);
        metaField = (igIntMetaField *)((igObjectDispatchView *)metaField)->CloneViaMetadata(1);
        metaField->_persistent = 0;
        metaField->_externalEnumStorage = (int)&k_capacity;
        igMetaObject_FinalizeAndReplaceField(metaObject, metaIndex, (::igMetaField *)metaField);
        metaField->release();
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->setDefault(64218);
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->setDefault(6);
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->_metaObject = (int)Gap::Core::igFile::getClassTypeLazy();
        metaField->_persistent = 0;
    }
    {
        igMemoryRefMetaField *metaField = (igMemoryRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 8);
        metaField->_memType = (int)Gap::Core::igCharMetaField::getMetaField();
    }
    {
        igRawRefMetaField *metaField = (igRawRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 18);
        metaField->_persistent = 0;
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 19);
        metaField->setDefault(-1);
    }
    {
        igMemoryRefMetaField *metaField = (igMemoryRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 21);
        metaField->_memType = (int)Gap::Core::igCharMetaField::getMetaField();
    }
    {
        igMemoryRefMetaField *metaField = (igMemoryRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 22);
        metaField->_memType = (int)Gap::Core::igCharMetaField::getMetaField();
    }
    {
        igMemoryRefMetaField *metaField = (igMemoryRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 23);
        metaField->_memType = (int)Gap::Core::igCharMetaField::getMetaField();
    }
    {
        igMemoryRefMetaField *metaField = (igMemoryRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 24);
        metaField->_memType = (int)Gap::Core::igCharMetaField::getMetaField();
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 25);
        metaField->_metaObject = (int)igMetaFieldList_GetOrCreateMetaObject();
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 26);
        metaField->_metaObject = (int)igMetaObjectList_GetOrCreateMetaObject();
    }
    {
        igMemoryRefMetaField *metaField = (igMemoryRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 28);
        metaField->_memType = (int)Gap::Core::igCharMetaField::getMetaField();
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 29);
        metaField->_metaObject = (int)Gap::Core::igMetaField::getClassTypeLazy();
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 30);
        metaField->_metaObject = (int)Gap::Core::igMetaField::getClassTypeLazy();
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 36);
        metaField->setDefault(-1);
    }
    {
        igMemoryRefMetaField *metaField = (igMemoryRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 37);
        metaField->_memType = (int)Gap::Core::igCharMetaField::getMetaField();
    }
    {
        igStringMetaField *metaField = (igStringMetaField *)igMetaObject_GetFieldAt(metaObject, start + 39);
        metaField->setDefault(0);
    }
    {
        igMemoryRefMetaField *metaField = (igMemoryRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 40);
        metaField->_memType = (int)Gap::Core::igCharMetaField::getMetaField();
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 42);
        metaField->_metaObject = (int)Gap::Core::igIntList::getClassTypeLazy();
    }
    {
        igMemoryRefMetaField *metaField = (igMemoryRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 44);
        metaField->_memType = (int)Gap::Core::igCharMetaField::getMetaField();
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 46);
        metaField->setDefault(-1);
    }
    {
        igMemoryRefMetaField *metaField = (igMemoryRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 47);
        metaField->_memType = (int)Gap::Core::igCharMetaField::getMetaField();
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 50);
        metaField->setDefault(-1);
    }
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 54);
        metaField->setDefault(1);
    }
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 55);
        metaField->setDefault(1);
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 57);
        metaField->_metaObject = (int)igMemoryPool_GetOrCreateMetaObject();
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 58);
        metaField->_metaObject = (int)igMemoryPool_GetOrCreateMetaObject();
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 59);
        metaField->_metaObject = (int)igMemoryPool_GetOrCreateMetaObject();
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 60);
        metaField->_metaObject = (int)Gap::Core::igObjectList::getClassTypeLazy();
    }
    {
        igMemoryRefMetaField *metaField = (igMemoryRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 63);
        metaField->_memType = (int)Gap::Core::igCharMetaField::getMetaField();
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 64);
        metaField->_metaObject = (int)Gap::Core::igIntList::getClassTypeLazy();
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}

void igIGBFile::arkRegisterUser()
{
    userRegister();
}
}
}

