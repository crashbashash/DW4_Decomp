igMetaObject *g_igIGBFile_metaObject;
int g_igIGBFile_dataDescriptorCell;
int g_igIGBFile_countDescriptorCell;
int g_igIGBFile_capacityDescriptorCell;
igMetaField *g_igIGBFile_magicCookieMetaField;
igMetaField *g_igIGBFile_magicVersionMetaField;
igMetaField *g_igIGBFile_fileMetaField;
igMetaField *g_igIGBFile_majorVersionMetaField;
igMetaField *g_igIGBFile_minorVersionMetaField;
igMetaField *g_igIGBFile_hasTemplatesMetaField;
igMetaField *g_igIGBFile_entryCountMetaField;
igMetaField *g_igIGBFile_indexBufferSizeMetaField;
igMetaField *g_igIGBFile_indexBufferMetaField;
igMetaField *g_igIGBFile_entryBufferSizeMetaField;
igMetaField *g_igIGBFile_metaObjectCountMetaField;
igMetaField *g_igIGBFile_metaObjectBufferSizeMetaField;
igMetaField *g_igIGBFile_metaFieldCountMetaField;
igMetaField *g_igIGBFile_metaFieldBufferSizeMetaField;
igMetaField *g_igIGBFile_objectCountMetaField;
igMetaField *g_igIGBFile_objectBufferSizeMetaField;
igMetaField *g_igIGBFile_memoryRefCountMetaField;
igMetaField *g_igIGBFile_memoryRefBufferSizeMetaField;
igMetaField *g_igIGBFile_userLoadFunctionMetaField;
igMetaField *g_igIGBFile_forceChunkSizeMetaField;
igMetaField *g_igIGBFile_endianSwapMetaField;
igMetaField *g_igIGBFile_metaObjectBufferMetaField;
igMetaField *g_igIGBFile_dirBufMetaField;
igMetaField *g_igIGBFile_objBufMetaField;
igMetaField *g_igIGBFile_mfBufMetaField;
igMetaField *g_igIGBFile_metaFieldListInFileMetaField;
igMetaField *g_igIGBFile_metaObjectListInFileMetaField;
igMetaField *g_igIGBFile_autoOpenedMetaField;
igMetaField *g_igIGBFile_basePathMetaField;
igMetaField *g_igIGBFile_imfMetaField;
igMetaField *g_igIGBFile_smfMetaField;
igMetaField *g_igIGBFile_hasInfoMetaField;
igMetaField *g_igIGBFile_hasExternalMetaField;
igMetaField *g_igIGBFile_sharedEntriesMetaField;
igMetaField *g_igIGBFile_hasVersion1CruftMetaField;
igMetaField *g_igIGBFile_version1CruftMultiplyMetaField;
igMetaField *g_igIGBFile_infoListPlaceField;
igMetaField *g_igIGBFile_externalDirectoryBufferMetaField;
igMetaField *g_igIGBFile_externalDirectoryBufferSizeMetaField;
igMetaField *g_igIGBFile_previousResourceFilePathMetaField;
igMetaField *g_igIGBFile_alignmentBufferMetaField;
igMetaField *g_igIGBFile_alignmentBufferSizeMetaField;
igMetaField *g_igIGBFile_alignmentListInFileMetaField;
igMetaField *g_igIGBFile_alignmentCountMetaField;
igMetaField *g_igIGBFile_objectBufferPlaceMetaField;
igMetaField *g_igIGBFile_memoryBufferPlaceMetaField;
igMetaField *g_igIGBFile_chunkSizeMetaField;
igMetaField *g_igIGBFile_chunkMetaField;
igMetaField *g_igIGBFile_chunkPlaceMetaField;
igMetaField *g_igIGBFile_bufferPlaceMetaField;
igMetaField *g_igIGBFile_bufferSizeMetaField;
igMetaField *g_igIGBFile_memoryBytesCopiedMetaField;
igMetaField *g_igIGBFile_bytesRemainingInChunkMetaField;
igMetaField *g_igIGBFile_hasCriticalFailureMetaField;
igMetaField *g_igIGBFile_autoReadFilePostProcessStateMetaField;
igMetaField *g_igIGBFile_autoWriteFilePostProcessStateMetaField;
igMetaField *g_igIGBFile_readFilePostProcessedStateMetaField;
igMetaField *g_igIGBFile_temporaryMemoryPoolMetaField;
igMetaField *g_igIGBFile_dataMemoryPoolMetaField;
igMetaField *g_igIGBFile_objectMemoryPoolMetaField;
igMetaField *g_igIGBFile_entryPoolMetaField;
igMetaField *g_igIGBFile_hasMemoryPoolNamesMetaField;
igMetaField *g_igIGBFile_memoryPoolNameBufferSizeMetaField;
igMetaField *g_igIGBFile_memoryPoolNameBufferMetaField;
igMetaField *g_igIGBFile_memoryPoolHandlesMetaField;

void * igIGBFile_Create(int pool) {
    igIGBFile_EnsureRegistered();
    return (void *)(igMetaObject_CreateInstance(g_igIGBFile_metaObject, (igMemoryPoolView *)pool));
}

int igIGBFile_GetOrCreateMetaObject(void) {
    if ((int)g_igIGBFile_metaObject == 0) {
        g_igIGBFile_metaObject = (igMetaObject *)(int)igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return (int)g_igIGBFile_metaObject;
}

igMetaObject *igIGBFile_GetMetaObject(void)
{
    igMetaObject *g = g_igIGBFile_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igIGBFile_EnsureRegistered();
    return g_igIGBFile_metaObject;
}

int igIGBFile_GetVTable(void) {
    igIGBFile file;
    int vtable;

    igDirectory_Construct(&file);
    file._vtable = (int)(&g_igIGBFile_vtable[0]);
    igSmartPointer_igObjectList_Construct(&file._entryPool);
    igSmartPointer_igFile_Construct(&file._file);
    igSmartPointer_igMetaFieldList_Construct(&file._metaFieldListInFile);
    igSmartPointer_igMetaObjectList_Construct(&file._metaObjectListInFile);
    igSmartPointer_igMetaField_Construct(&file.imf);
    igSmartPointer_igMetaField_Construct(&file.smf);
    igStringRef_Construct(&file._previousResourceFilePath);
    igSmartPointer_igIntList_Construct(&file._alignmentListInFile);
    igSmartPointer_igMemoryPool_Construct(&file._temporaryMemoryPool);
    igSmartPointer_igMemoryPool_Construct(&file._dataMemoryPool);
    igSmartPointer_igMemoryPool_Construct(&file._objectMemoryPool);
    igSmartPointer_igIntList_Construct(&file._memoryPoolHandles);
    vtable = *(int *)((char *)&file + g_objectSystem->vtableProbeOffset);
    file._vtable = (int)(&g_igInfo_vtable[28]); /* matching construct: igIGBFile's vtable address (it follows igInfo's 28 words) spelled through another symbol, so it is rematerialised rather than reused */
    igSmartPointer_igIntList_Destruct(&file._memoryPoolHandles, -1);
    igSmartPointer_igMemoryPool_Destruct(&file._objectMemoryPool, -1);
    igSmartPointer_igMemoryPool_Destruct(&file._dataMemoryPool, -1);
    igSmartPointer_igMemoryPool_Destruct(&file._temporaryMemoryPool, -1);
    igSmartPointer_igIntList_Destruct(&file._alignmentListInFile, -1);
    igStringRef_Destruct(&file._previousResourceFilePath, -1);
    igSmartPointer_igMetaField_Destruct(&file.smf, -1);
    igSmartPointer_igMetaField_Destruct(&file.imf, -1);
    igSmartPointer_igMetaObjectList_Destruct(&file._metaObjectListInFile, -1);
    igSmartPointer_igMetaFieldList_Destruct(&file._metaFieldListInFile, -1);
    igSmartPointer_igFile_Destruct(&file._file, -1);
    igSmartPointer_igObjectList_Destruct(&file._entryPool, -1);
    igDirectory_Destroy((igDirectory *)&file, 0);
    return vtable;
}

igSmartPointer<igObject> *igSmartPointer_igShortListList_Destruct(igSmartPointer<igObject> *self,int delete_storage) {
    if(self) {
        igObject *object=self->p;
        if(object) {
            --object->_refCount;
            if(((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL)==0)
                igObject_Destroy((void *)object);
        }
        if((short)delete_storage>0) __dl__FPv(self);
    }
    return self;
}

igDirectory *igDirectory_Destroy(igDirectory *p, short n) {
    if (p) {
        p->_vtable = (int)&g_igDirectory_vtable[0];
        ((igSmartPointer<igObject> *)&p->_loadingSemaphore)->~igSmartPointer();
        ((igSmartPointer<igObject> *)&p->_metaFieldPerObjectIndices)->~igSmartPointer();
        ((igSmartPointer<igObject> *)&p->_refList)->~igSmartPointer();
        ((igSmartPointer<igObject> *)&p->_uniqueEntryList)->~igSmartPointer();
        ((igSmartPointer<igObject> *)&p->_infoList)->~igSmartPointer();
        ((igSmartPointer<igObject> *)&p->_externalDirectoryList)->~igSmartPointer();
        ((igStringRef *)&p->_name)->~igStringRef();
        if (n > 0) Memory_FreeBufferAliasC(p);
    }
    return p;
}

int *igSmartPointer_igMemoryPool_Construct(int *p)
{
    *p = 0;
    return p;
}

int *igSmartPointer_igMetaField_Construct(int *p)
{
    *p = 0;
    return p;
}

int *igSmartPointer_igMetaFieldList_Construct(int *p)
{
    *p = 0;
    return p;
}

int *igSmartPointer_igFile_Construct(int *p)
{
    *p = 0;
    return p;
}

int *igSmartPointer_igObjectList_Construct(int *p)
{
    *p = 0;
    return p;
}

void *igDirectory_Construct(igIGBFile *self) {
    igObject_InitHeader((igObject *)self);
    self->_vtable = (int)(&g_igDataList_vtable[0]);
    self->_vtable = (int)(&g_igObjectListBase_vtable[0]);
    self->_vtable = (int)(&g_igObjectList_vtable[0]);
    self->_vtable = (int)(&g_igDirectoryBase_vtable[0]);
    self->_vtable = (int)(&g_igDirectory_vtable[0]);
    self->_name = 0;
    self->_externalDirectoryList = 0;
    self->_infoList = 0;
    self->_uniqueEntryList = 0;
    self->_refList = 0;
    self->_metaFieldPerObjectIndices = 0;
    self->_loadingSemaphore = 0;
    return self;
}

void igIGBFile_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igIGBFile_Register);
}

static igMetaObjectCallback g_igIGBFile_callbackList[] = { igFile_EnsureRegistered, igMetaFieldList_EnsureRegistered, igMetaObjectList_EnsureRegistered, igMetaField_EnsureRegistered, igIntList_EnsureRegistered, igMemoryPool_EnsureRegistered, igObjectList_EnsureRegistered, 0 };

CallbackArray *igIGBFile_Register(void) {
    CoreLibrary_MarkRegistered();  /* First-use initializer: sets a gp byte flag, then runs five one-time init calls. */
    return igMetaObject_RegisterClass(
        0,
        &g_igIGBFile_metaObject,
        igDirectory_Register,
        igDirectory_GetPublishedMetaObject,
        igIGBFile_GetMetaObjectFunction,
        "igIGBFile",
        sizeof(igIGBFile),
        igIGBFile_GetVTable,
        igIGBFile_InitFields,
        igIGBFile_StaticInitCallback,
        g_igIGBFile_callbackList
    );
}

void igIGBFile_GetMetaObjectFunction(void) {
    igIGBFile_GetMetaObject();
}

igMetaObject *g_igDirectory_metaObject;
igMetaField *g_igDirectory_nameField;
igMetaField *g_igDirectory_externalDirectoryListMetaField;
igMetaField *g_igDirectory_infoListMetaField;
igMetaField *g_igDirectory_managingResourceMetaField;
igMetaField *g_igDirectory_loadPendingStateMetaField;
igMetaField *g_igDirectory_validStateMetaField;
igMetaField *g_igDirectory_compatibleStateMetaField;
igMetaField *g_igDirectory_loadedRefCountMetaField;
igMetaField *g_igDirectory_metaFieldPerObjectIndicesMetaField;
igMetaField *g_igDirectory_concreteStateMetaField;
igMetaField *g_igDirectory_sharingStateMetaField;
igMetaField *g_igDirectory_trackUniqueEntriesMetaField;
igMetaField *g_igDirectory_uniqueEntryListMetaField;
igMetaField *g_igDirectory_refListMetaField;
igMetaField *g_igDirectory_autoWriteFilePreProcessStateMetaField;
igMetaField *g_igDirectory_useMemoryPoolAssignmentsStateMetaField;
igMetaField *g_igDirectory_forceWriteMemoryPoolInfoFromMetaStateMetaField;
igMetaField *g_igDirectory_loadingSemaphoreMetaField;
int g_igDirEntry_refTypeMetaEnum;
int g_igDirEntry_resolveMethodMetaEnum;

igMetaObject *igDirectory_GetPublishedMetaObject(void) {
    return g_igDirectory_metaObject;
}

static FieldFactory g_igIGBFile_ctorTable[] = {
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igMemoryRefMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igRawRefMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igMemoryRefMetaField_Create,
    (FieldFactory)igMemoryRefMetaField_Create,
    (FieldFactory)igMemoryRefMetaField_Create,
    (FieldFactory)igMemoryRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igMemoryRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igMemoryRefMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igStringMetaField_Create,
    (FieldFactory)igMemoryRefMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igMemoryRefMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igMemoryRefMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igMemoryRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
};
static const char *g_igIGBFile_fieldTable[] = {
    "_magicCookie",
    "_magicVersion",
    "_file",
    "_majorVersion",
    "_minorVersion",
    "_hasTemplates",
    "_entryCount",
    "_indexBufferSize",
    "_indexBuffer",
    "_entryBufferSize",
    "_metaObjectCount",
    "_metaObjectBufferSize",
    "_metaFieldCount",
    "_metaFieldBufferSize",
    "_objectCount",
    "_objectBufferSize",
    "_memoryRefCount",
    "_memoryRefBufferSize",
    "_userLoadFunction",
    "_forceChunkSize",
    "_endianSwap",
    "_metaObjectBuffer",
    "_dirBuf",
    "_objBuf",
    "_mfBuf",
    "_metaFieldListInFile",
    "_metaObjectListInFile",
    "_autoOpened",
    "_basePath",
    "imf",
    "smf",
    "_hasInfo",
    "_hasExternal",
    "_sharedEntries",
    "_hasVersion1Cruft",
    "_version1CruftMultiply",
    "_infoListPlace",
    "_externalDirectoryBuffer",
    "_externalDirectoryBufferSize",
    "_previousResourceFilePath",
    "_alignmentBuffer",
    "_alignmentBufferSize",
    "_alignmentListInFile",
    "_alignmentCount",
    "_objectBufferPlace",
    "_memoryBufferPlace",
    "_chunkSize",
    "_chunk",
    "_chunkPlace",
    "_bufferPlace",
    "_bufferSize",
    "_memoryBytesCopied",
    "_bytesRemainingInChunk",
    "_hasCriticalFailure",
    "_autoReadFilePostProcessState",
    "_autoWriteFilePostProcessState",
    "_readFilePostProcessedState",
    "_temporaryMemoryPool",
    "_dataMemoryPool",
    "_objectMemoryPool",
    "_entryPool",
    "_hasMemoryPoolNames",
    "_memoryPoolNameBufferSize",
    "_memoryPoolNameBuffer",
    "_memoryPoolHandles",
};
static igMetaField **g_igIGBFile_fieldDescriptors[] = {
    &g_igIGBFile_magicCookieMetaField,
    &g_igIGBFile_magicVersionMetaField,
    &g_igIGBFile_fileMetaField,
    &g_igIGBFile_majorVersionMetaField,
    &g_igIGBFile_minorVersionMetaField,
    &g_igIGBFile_hasTemplatesMetaField,
    &g_igIGBFile_entryCountMetaField,
    &g_igIGBFile_indexBufferSizeMetaField,
    &g_igIGBFile_indexBufferMetaField,
    &g_igIGBFile_entryBufferSizeMetaField,
    &g_igIGBFile_metaObjectCountMetaField,
    &g_igIGBFile_metaObjectBufferSizeMetaField,
    &g_igIGBFile_metaFieldCountMetaField,
    &g_igIGBFile_metaFieldBufferSizeMetaField,
    &g_igIGBFile_objectCountMetaField,
    &g_igIGBFile_objectBufferSizeMetaField,
    &g_igIGBFile_memoryRefCountMetaField,
    &g_igIGBFile_memoryRefBufferSizeMetaField,
    &g_igIGBFile_userLoadFunctionMetaField,
    &g_igIGBFile_forceChunkSizeMetaField,
    &g_igIGBFile_endianSwapMetaField,
    &g_igIGBFile_metaObjectBufferMetaField,
    &g_igIGBFile_dirBufMetaField,
    &g_igIGBFile_objBufMetaField,
    &g_igIGBFile_mfBufMetaField,
    &g_igIGBFile_metaFieldListInFileMetaField,
    &g_igIGBFile_metaObjectListInFileMetaField,
    &g_igIGBFile_autoOpenedMetaField,
    &g_igIGBFile_basePathMetaField,
    &g_igIGBFile_imfMetaField,
    &g_igIGBFile_smfMetaField,
    &g_igIGBFile_hasInfoMetaField,
    &g_igIGBFile_hasExternalMetaField,
    &g_igIGBFile_sharedEntriesMetaField,
    &g_igIGBFile_hasVersion1CruftMetaField,
    &g_igIGBFile_version1CruftMultiplyMetaField,
    &g_igIGBFile_infoListPlaceField,
    &g_igIGBFile_externalDirectoryBufferMetaField,
    &g_igIGBFile_externalDirectoryBufferSizeMetaField,
    &g_igIGBFile_previousResourceFilePathMetaField,
    &g_igIGBFile_alignmentBufferMetaField,
    &g_igIGBFile_alignmentBufferSizeMetaField,
    &g_igIGBFile_alignmentListInFileMetaField,
    &g_igIGBFile_alignmentCountMetaField,
    &g_igIGBFile_objectBufferPlaceMetaField,
    &g_igIGBFile_memoryBufferPlaceMetaField,
    &g_igIGBFile_chunkSizeMetaField,
    &g_igIGBFile_chunkMetaField,
    &g_igIGBFile_chunkPlaceMetaField,
    &g_igIGBFile_bufferPlaceMetaField,
    &g_igIGBFile_bufferSizeMetaField,
    &g_igIGBFile_memoryBytesCopiedMetaField,
    &g_igIGBFile_bytesRemainingInChunkMetaField,
    &g_igIGBFile_hasCriticalFailureMetaField,
    &g_igIGBFile_autoReadFilePostProcessStateMetaField,
    &g_igIGBFile_autoWriteFilePostProcessStateMetaField,
    &g_igIGBFile_readFilePostProcessedStateMetaField,
    &g_igIGBFile_temporaryMemoryPoolMetaField,
    &g_igIGBFile_dataMemoryPoolMetaField,
    &g_igIGBFile_objectMemoryPoolMetaField,
    &g_igIGBFile_entryPoolMetaField,
    &g_igIGBFile_hasMemoryPoolNamesMetaField,
    &g_igIGBFile_memoryPoolNameBufferSizeMetaField,
    &g_igIGBFile_memoryPoolNameBufferMetaField,
    &g_igIGBFile_memoryPoolHandlesMetaField,
};
static int g_igIGBFile_fieldOffsets[] = {
    96,
    100,
    104,
    72,
    76,
    108,
    112,
    116,
    120,
    124,
    128,
    132,
    136,
    140,
    144,
    148,
    152,
    156,
    160,
    164,
    168,
    172,
    176,
    180,
    184,
    188,
    192,
    196,
    200,
    204,
    208,
    212,
    213,
    214,
    215,
    216,
    220,
    224,
    228,
    232,
    236,
    240,
    244,
    248,
    252,
    256,
    260,
    264,
    80,
    84,
    88,
    268,
    272,
    276,
    277,
    278,
    279,
    280,
    284,
    288,
    92,
    292,
    296,
    300,
    304,
};


void igIGBFile_InitFields(void) {
    igMetaObject *meta = g_igIGBFile_metaObject;
    int base = igMetaObject_GetFieldCount(meta);
    igMetaField *field;
    igMetaField *clone;
    int index;
    igMetaObject_CreateFields(meta, g_igIGBFile_ctorTable, 0x41);
    field = ((igMetaField *)igMetaObject_FindFieldByName(meta, (const char *)data));
    index = ObjectPointerList_FindIndex((char *)meta->_metaFields, (int)field);
    clone = (igMetaField *)((igObjectDispatchView *)field)->CloneViaMetadata(1);
    clone->_persistent = 0;
    clone->_externalEnumStorage = (int)&g_igIGBFile_dataDescriptorCell;
    igMetaObject_FinalizeAndReplaceField(meta, index, clone);
    releaseField(clone);
    field = ((igMetaField *)igMetaObject_FindFieldByName(meta, (const char *)text_count));
    index = ObjectPointerList_FindIndex((char *)meta->_metaFields, (int)field);
    clone = (igMetaField *)((igObjectDispatchView *)field)->CloneViaMetadata(1);
    clone->_persistent = 0;
    clone->_externalEnumStorage = (int)&g_igIGBFile_countDescriptorCell;
    igMetaObject_FinalizeAndReplaceField(meta, index, clone);
    releaseField(clone);
    field = ((igMetaField *)igMetaObject_FindFieldByName(meta, (const char *)text_capacity));
    index = ObjectPointerList_FindIndex((char *)meta->_metaFields, (int)field);
    clone = (igMetaField *)((igObjectDispatchView *)field)->CloneViaMetadata(1);
    clone->_persistent = 0;
    clone->_externalEnumStorage = (int)&g_igIGBFile_capacityDescriptorCell;
    igMetaObject_FinalizeAndReplaceField(meta, index, clone);
    releaseField(clone);
    igIntMetaField_SetDefault((void **)(((igMetaField *)igMetaObject_GetFieldAt(meta, base))), 0xFADA);
    igIntMetaField_SetDefault((void **)(((igMetaField *)igMetaObject_GetFieldAt(meta, base + 1))), 6);
    field = ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 2));
    ((igObjectRefMetaField *)field)->_metaObject = (int)igFile_GetOrCreateMetaObject();
    ((igMetaField *)field)->_persistent = 0;
    field = ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 8));
    ((igMemoryRefMetaField *)field)->_memType = igCharMetaField_GetDefaultDescriptor();
    ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x12))->_persistent = 0;
    igIntMetaField_SetDefault((void **)(((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x13))), -1);
    field = ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x15));
    ((igMemoryRefMetaField *)field)->_memType = igCharMetaField_GetDefaultDescriptor();
    field = ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x16));
    ((igMemoryRefMetaField *)field)->_memType = igCharMetaField_GetDefaultDescriptor();
    field = ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x17));
    ((igMemoryRefMetaField *)field)->_memType = igCharMetaField_GetDefaultDescriptor();
    field = ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x18));
    ((igMemoryRefMetaField *)field)->_memType = igCharMetaField_GetDefaultDescriptor();
    field = ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x19));
    ((igObjectRefMetaField *)field)->_metaObject = (int)igMetaFieldList_GetOrCreateMetaObject();
    field = ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x1A));
    ((igObjectRefMetaField *)field)->_metaObject = (int)igMetaObjectList_GetOrCreateMetaObject();
    field = ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x1C));
    ((igMemoryRefMetaField *)field)->_memType = igCharMetaField_GetDefaultDescriptor();
    field = ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x1D));
    ((igObjectRefMetaField *)field)->_metaObject = (int)igMetaField_GetOrCreateMetaObject();
    field = ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x1E));
    ((igObjectRefMetaField *)field)->_metaObject = (int)igMetaField_GetOrCreateMetaObject();
    igIntMetaField_SetDefault((void **)(((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x24))), -1);
    field = ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x25));
    ((igMemoryRefMetaField *)field)->_memType = igCharMetaField_GetDefaultDescriptor();
    igStringMetaField_SetDefaultText((int *)(((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x27))), 0);
    field = ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x28));
    ((igMemoryRefMetaField *)field)->_memType = igCharMetaField_GetDefaultDescriptor();
    field = ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x2A));
    ((igObjectRefMetaField *)field)->_metaObject = igIntList_GetOrCreateMetaObject();
    field = ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x2C));
    ((igMemoryRefMetaField *)field)->_memType = igCharMetaField_GetDefaultDescriptor();
    igIntMetaField_SetDefault((void **)(((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x2E))), -1);
    field = ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x2F));
    ((igMemoryRefMetaField *)field)->_memType = igCharMetaField_GetDefaultDescriptor();
    igIntMetaField_SetDefault((void **)(((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x32))), -1);
    igBoolMetaField_SetDefaultValue((void **)(((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x36))), 1);
    igBoolMetaField_SetDefaultValue((void **)(((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x37))), 1);
    field = ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x39));
    ((igObjectRefMetaField *)field)->_metaObject = (int)igMemoryPool_GetOrCreateMetaObject();
    field = ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x3A));
    ((igObjectRefMetaField *)field)->_metaObject = (int)igMemoryPool_GetOrCreateMetaObject();
    field = ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x3B));
    ((igObjectRefMetaField *)field)->_metaObject = (int)igMemoryPool_GetOrCreateMetaObject();
    field = ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x3C));
    ((igObjectRefMetaField *)field)->_metaObject = igObjectList_GetOrCreateMetaObject();
    field = ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x3F));
    ((igMemoryRefMetaField *)field)->_memType = igCharMetaField_GetDefaultDescriptor();
    field = ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x40));
    ((igObjectRefMetaField *)field)->_metaObject = igIntList_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_igIGBFile_fieldTable, g_igIGBFile_fieldDescriptors, g_igIGBFile_fieldOffsets, base);
}

void igIGBFile_StaticInitCallback(void) {
    igIGBFile_RegisterBlindObjectsConfig();
}

