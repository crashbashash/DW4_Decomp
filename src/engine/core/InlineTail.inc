int igPsx2IopRpcConnection_GetMeta(void)
{
    return (int)g_igPsx2IopRpcConnection_metaObject;
}

igMetaObject *igPsx2Folder_GetMeta(void) {
    return g_igPsx2Folder_metaObject;
}

int igPsx2File_GetMeta(void) {
    return (int)g_igPsx2File_metaObject;
}

void igPsx2File_InitDefaults(igPsx2File *self) {
    int *header;
    int prefix;
    int count;
    int pool;
    int *old;
    int *interned;
    prefix = g_igPsx2File_defaultPrefix;
    if (g_stringPool == 0) {
        pool = ((int)StringPool_Allocate(0x10));
        if (pool != 0) {
            pool = ((int)StringPool_Construct((StringPool *)pool));
        }
        g_stringPool = (StringPool *)pool;
    }
    interned = (int *)(((void *)StringPool_Intern((StringPool *)g_stringPool, (const char *)prefix)));
    old = (int *)self->_prefix;
    if (old != 0) {
        header = old - 2;
        count = old[-1] - 1;
        old[-1] = count;
        if (count == 0) {
            StringChunk_ReleaseHeader((StringChunk *)(*header), (StringTokenHeader *)header);
        }
    }
    self->_prefix = (int)interned;
}

int igPsx2CallStackTracer_GetMeta(void)
{
    return (int)g_igPsx2CallStackTracer_metaObject;
}

void igUnsignedIntListNoClean_TrimCapacity(void) {

}

int igStandardQueue_GetMeta(void) {
    return (int)g_igStandardQueue_metaObject;
}

igMetaObject *igStackMemoryPool_GetMeta(void) {
    return g_igStackMemoryPool_metaObject;
}

unsigned char igStackMemoryPool_IsAlchemyMemory(igStackMemoryPool *self) {
    return self->_isAlchemyMemory;
}

/* igStackMemoryPool vtable slot 29 (+0x74): constant leaf returning 1. The igArenaMemoryPool and
 * igMallocMemoryPool versions return 0 and igPageMemoryPool returns 1. */
int igStackMemoryPool_IsSecondaryAllocator(igStackMemoryPool *self) {
    return 1;
}

void igStackMemoryPool_SetMaxSize(int *status_out) {
    *status_out = g_resultFailure.v;
}

int Gap__Core__igStackMemoryPool__vfunc_83(void) {
    return 1;
}

int igProgramFile_GetMeta(void)
{
    return (int)g_igProgramFile_metaObject;
}

int igElfFile_GetMeta(void) {
    return (int)g_igElfFile_metaObject;
}

int igSymbolTable_GetMeta(void) {
    return (int)g_igSymbolTable_metaObject;
}

int igStringTable_GetMeta(void) {
    return (int)g_igStringTable_metaObject;
}

igMetaObject *igStringRefList_GetMeta(void) {
    return g_igStringRefList_metaObject;
}

void igStringRefList_UserPreWrite(igObjectDispatchView *self)
{
    self->TrimCapacity();
}

void igStringRefList_TrimCapacity(igStringRefList *l) {
    int n = l->_count;
    if (n < l->_capacity) {
        List_Reserve((igDataList *)l, n, 4);
    }
}

int igResource_GetMeta(void) {
    return (int)g_igResource_metaObject;
}

igMetaObject *igRegistry_GetMeta(void) {
    return g_igRegistry_metaObject;
}

igMetaObject *igQueue_GetMeta(void) {
    return g_igQueue_metaObject;
}

int igPluginHelper_GetMeta(void) {
    return (int)g_igPluginHelper_metaObject;
}

int igNamedObjectInfo_GetMeta(void) {
    return (int)g_igNamedObjectInfo_metaObject;
}

igMetaObject *igMetaFieldInfo_GetMeta(void) {
    return g_igMetaFieldInfo_metaObject;
}

int igMemoryPoolInfo_GetMeta(void) {
    return (int)g_igMemoryPoolInfo_metaObject;
}

igMetaObject *igMemoryPoolContextInfo_GetMeta(void) {
    return g_igMemoryPoolContextInfo_metaObject;
}


int MemoryContext_GetMeta(void) {
    return g_MemoryContext_metaObject;
}

int igMemoryFile_GetMeta(void) {
    return (int)g_igMemoryFile_metaObject;
}

int igMemoryDictionary_GetMeta(void) {
    return (int)g_igMemoryDictionary_metaObject;
}

igMetaObject *igMediaFile_GetMeta(void) {
    return g_igMediaFile_metaObject;
}

int igLocationTable_GetMeta(void) {
    return (int)g_igLocationTable_metaObject;
}

int igIGBFile_GetMeta(void) {
    return (int)g_igIGBFile_metaObject;
}

igMetaObject *igFolder_GetMeta(void) {
    return g_igFolder_metaObject;
}

igMetaObject *igFile_GetMeta(void) {
    return g_igFile_metaObject;
}

int igExternalInfoEntry_GetMeta(void) {
    return (int)g_igExternalInfoEntry_metaObject;
}

int igExternalIndexedEntry_GetMeta(void) {
    return (int)g_igExternalIndexedEntry_metaObject;
}

int igExternalDirEntry_GetMeta(void) {
    return (int)g_igExternalDirEntry_metaObject;
}

int igEventTracker_GetMeta(void) {
    return (int)g_igEventTracker_metaObject;
}

int igDriverDatabase_GetMeta(void) {
    return (int)g_igDriverDatabase_metaObject;
}

int igDirectory_GetMeta(void) {
    return (int)g_igDirectory_metaObject;
}

int igCallStackTracer_GetMeta(void) {
    return (int)g_igCallStackTracer_metaObject;
}

igMetaObject *igCallStackTable_GetMeta(void) {
    return g_igCallStackTable_metaObject;
}

int igMemoryDescriptorMetaField_GetMeta(void) {
    return (int)g_igMemoryDescriptorMetaField_metaObject;
}

int igMemoryDescriptorMetaField_GetDescriptor(void) {
    return (int)g_igMemoryDescriptorMetaField_descriptor;
}

int igMallocMemoryPool_GetMeta(void) {
    return (int)g_igMallocMemoryPool_metaObject;
}

void igMallocMemoryPool_ReleaseDefaults(igMemoryPoolView *self) {
    g_igMallocMemoryPool_instanceCount = (g_igMallocMemoryPool_instanceCount + -1);
    igMemoryPool_ReleaseDefaults(self);
}

void igMallocMemoryPool_Reset(void) {

}

/* Deactivates the pool: clears the reflected _isActive flag (igBoolMetaField, +112). */
void igMallocMemoryPool_Deactivate(igMallocMemoryPool *self) {
    self->_isActive = 0;
}

void igMallocMemoryPool_SetRawMemory(int *statusOut) {
    *statusOut = g_resultFailure.v;
}

int igMallocMemoryPool_IsAlchemyMemory(void) {
    return 0;
}

int igMallocMemoryPool_GetRawMemory(void) {
    return 0;
}

int igMallocMemoryPool_IsSecondaryAllocator(void) {
    return 0;
}

int igArenaMemoryPool_GetMeta(void) {
    return (int)g_igArenaMemoryPool_metaObject;
}

int igPageMemoryPool_GetMeta(void) {
    return (int)g_igPageMemoryPool_metaObject;
}

int igAliasMemoryPool_GetMeta(void) {
    return (int)g_igAliasMemoryPool_metaObject;
}

int Gap__Core__igAliasMemoryPool__vfunc_83(void) {
    return 1;
}

int igContextList_GetMeta(void) {
    return (int)g_igContextList_metaObject;
}

igMetaObject *igContextExtInfo_GetMeta(void) {
    return g_igContextExtInfo_metaObject;
}

igMetaObject *igContextExtInfoList_GetMeta(void) {
    return g_igContextExtInfoList_metaObject;
}

igMetaObject *igContextExtList_GetMeta(void) {
    return g_igContextExtList_metaObject;
}

igMetaObject *igBoolList_GetMeta(void) {
    return g_igBoolList_metaObject;
}

igMetaObject *igCharListNoClean_GetMeta(void) {
    return g_igCharListNoClean_metaObject;
}

void igCharListNoClean_TrimCapacity(void) {

}

igMetaObject *igCharList_GetMeta(void) {
    return g_igCharList_metaObject;
}

igMetaObject *igIntListNoClean_GetMeta(void) {
    return g_igIntListNoClean_metaObject;
}

void igIntListNoClean_TrimCapacity(void) {

}

int igIntList_GetMetaObject_Virtual(void) {
    return (int)g_igIntList_metaObject;
}

igMetaObject *igLongList_GetMeta(void) {
    return g_igLongList_metaObject;
}

igMetaObject *igUnsignedIntListNoClean_GetMeta(void) {
    return g_igUnsignedIntListNoClean_metaObject;
}

igMetaObject *igUnsignedShortList_GetMeta(void) {
    return g_igUnsignedShortList_metaObject;
}

igMetaObject *igShortList_GetMeta(void) {
    return g_igShortList_metaObject;
}

igMetaObject *igShortListList_GetMeta(void) {
    return g_igShortListList_metaObject;
}

int igUnsignedCharList_GetMeta(void) {
    return (int)g_igUnsignedCharList_metaObject;
}

igMetaObject *igFloatList_GetMeta(void) {
    return g_igFloatList_metaObject;
}

igMetaObject *igFloatListList_GetMeta(void) {
    return g_igFloatListList_metaObject;
}

igMetaObject *igPointerList_GetMeta(void) {
    return g_igPointerList_metaObject;
}

igMetaObject *igPointerListList_GetMeta(void) {
    return g_igPointerListList_metaObject;
}

igMetaObject *igMetaObjectList_GetMeta(void) {
    return g_igMetaObjectList_metaObject;
}

igMetaObject *igMetaObjectListList_GetMeta(void) {
    return g_igMetaObjectListList_metaObject;
}

igMetaObject *igMetaFieldList_GetMeta(void) {
    return g_igMetaFieldList_metaObject;
}

igMetaObject *igIntListList_GetMeta(void) {
    return g_igIntListList_metaObject;
}

igMetaObject *igObjectListList_GetMeta(void) {
    return g_igObjectListList_metaObject;
}

igMetaObject *igStringRefListList_GetMeta(void) {
    return g_igStringRefListList_metaObject;
}

igMetaObject *igDependencyMetaField_GetMeta(void) {
    return g_igDependencyMetaField_metaObject;
}

int igDependencyMetaField_GetDescriptor(void) {
    return (*(int *)&g_igDependencyMetaField_descriptor);
}

int igDependencyList_GetMeta(void) {
    return (int)g_igDependencyList_metaObject;
}

igMetaObject *igDirectoryList_GetMeta(void) {
    return g_igDirectoryList_metaObject;
}

int igErrorHandler_GetMeta(void) {
    return (int)g_igErrorHandler_metaObject;
}

int igInfoList_GetMeta(void) {
    return (int)g_igInfoList_metaObject;
}

igMetaObject *__internalNonRefCountedObjectList_GetMeta(void) {
    return g___internalNonRefCountedObjectList_metaObject;
}

igMetaObject *__internalObjectList_GetMeta(void) {
    return g___internalObjectList_metaObject;
}

int igLibraryList_GetMeta(void) {
    return (int)g_igLibraryList_metaObject;
}

igMetaObject *igMediaList_GetMeta(void) {
    return g_igMediaList_metaObject;
}

igMetaObject *igMemoryFileEntry_GetMeta(void) {
    return g_igMemoryFileEntry_metaObject;
}

igMetaObject *igMemoryFileEntryList_GetMeta(void) {
    return g_igMemoryFileEntryList_metaObject;
}

igMetaObject *igMemoryPoolInfoList_GetMeta(void) {
    return g_igMemoryPoolInfoList_metaObject;
}

int igMetaEnum_GetMeta(void) {
    return (int)g_igMetaEnum_metaObject;
}

igMetaObject *igNamedObjectList_GetMeta(void) {
    return g_igNamedObjectList_metaObject;
}

int igObjectStringMap_GetMeta(void) {
    return (int)g_igObjectStringMap_metaObject;
}

int igPluginRepository_GetMeta(void) {
    return (int)g_igPluginRepository_metaObject;
}

igMetaObject *igPluginRepositoryList_GetMeta(void) {
    return g_igPluginRepositoryList_metaObject;
}

int igRegistryValue_GetMeta(void) {
    return (int)g_igRegistryValue_metaObject;
}

igMetaObject *igRegistryValueList_GetMeta(void) {
    return g_igRegistryValueList_metaObject;
}

int igStringObj_GetMeta(void) {
    return (int)g_igStringObj_metaObject;
}

igMetaObject *igStringObjList_GetMeta(void) {
    return g_igStringObjList_metaObject;
}

igMetaObject *igThreadList_GetMeta(void) {
    return g_igThreadList_metaObject;
}

igMetaObject *igNonRefCountedThreadList_GetMeta(void) {
    return g_igNonRefCountedThreadList_metaObject;
}

int igContextList_GetElementMeta(void) {
    return (int)g_igContext_metaObject;
}

igMetaObject *igNonRefCountedThreadList_GetElementMeta(void) {
    return g_igThread_metaObject;
}

/* Element size in bytes of the list's items: 8. The same class's TrimCapacity (vfunc_18) re-sizes
 * the buffer with List_Reserve(self, count, 8), and the sibling lists igCharMetricsList (0x28) and
 * igPsx2AudioSourceList (0x24) return their item size from this same slot 23. */
int igDependencyList_GetElementSize(void) {
    return 8;
}

int igPointerList_GetElementSize(void) {
    return 4;
}

int List_LowerBoundWords(igTDataList<unsigned int> *list, unsigned int *key) {
    unsigned int value;
    int lo;
    int hi;
    int mid;
    unsigned int k;
    int n;
    lo = 0;
    n = list->_count;
    hi = n - 1;
    while (lo < hi) {
        mid = (lo + hi) >> 1;
        k = *key;
        value = list->_data[mid];
        if (value < k) {
            lo = 1 + mid;
        } else if (k < value) {
            hi = mid - 1;
        } else {
            return mid;
        }
    }
    if (!n) return 0;
    lo = (list->_data[lo] < *key) ? lo + 1 : lo;
    return lo;
}

int igFloatList_GetElementSize(void) {
    return 4;
}

int igUnsignedCharList_GetElementSize(void) {
    return 1;
}

int igShortList_GetElementSize(void) {
    return 2;
}

int igUnsignedShortList_GetElementSize(void) {
    return 2;
}

int igIntList_GetElementSize(void) {
    return 4;
}

int igCharList_GetElementSize(void) {
    return 1;
}

int igBoolList_GetElementSize(void) {
    return 1;
}

int igStringRefList_GetElementSize(void) {
    return 4;
}

igMetaObject *igContextExtList_GetElementMeta(void) {
    return g_igContextExt_metaObject;
}

igMetaObject *igContextExtInfoList_GetElementMeta(void) {
    return g_igContextExtInfo_metaObject;
}

igMetaObject *igMediaList_GetElementMeta(void) {
    return g_igMedia_metaObject;
}

igMetaObject *igMemoryFileEntryList_GetElementMeta(void) {
    return g_igMemoryFileEntry_metaObject;
}

igMetaObject *igMemoryPoolInfoList_GetElementMeta(void) {
    return g_igMemoryPoolInfo_metaObject;
}

int igInfoList_GetElementMeta(void) {
    return (int)g_igInfo_metaObject;
}

int igPluginRepositoryList_GetElementMeta(void) {
    return (int)g_igPluginRepository_metaObject;
}

igMetaObject *igRegistryValueList_GetElementMeta(void) {
    return g_igRegistryValue_metaObject;
}

igMetaObject *igDirectoryList_GetElementMeta(void) {
    return g_igDirectory_metaObject;
}

igMetaObject *igDirectory_GetElementMeta(void) {
    return g_igDirEntry_metaObject;
}

igMetaObject *igStringObjList_GetElementMeta(void) {
    return g_igStringObj_metaObject;
}

igMetaObject *igThreadList_GetElementMeta(void) {
    return g_igThread_metaObject;
}

int beDataObjList_GetElementMeta(void)
{
    return (int)g_igNamedObject_metaObject;
}

int igLibraryList_GetElementMeta(void) {
    return (int)g_igLibrary_metaObject;
}

igMetaObject *igStringRefListList_GetElementMeta(void) {
    return g_igStringRefList_metaObject;
}

igMetaObject *igObjectListList_GetElementMeta(void) {
    return g_igObjectList_metaObject;
}

igMetaObject *igIntListList_GetElementMeta(void) {
    return g_igIntList_metaObject;
}

igMetaObject *igMetaFieldList_GetElementMeta(void) {
    return Gap::Core::igMetaField::getClassMeta();
}

igMetaObject *igMetaObjectListList_GetElementMeta(void) {
    return g_igMetaObjectList_metaObject;
}

igMetaObject *igMetaObjectList_GetElementMeta(void) {
    return g_igMetaObject_metaObject;
}

igMetaObject *igPointerListList_GetElementMeta(void) {
    return g_igPointerList_metaObject;
}

igMetaObject *igFloatListList_GetElementMeta(void) {
    return g_igFloatList_metaObject;
}

igMetaObject *igShortListList_GetElementMeta(void) {
    return g_igShortList_metaObject;
}

void igBoolList_TrimCapacity(igDataList *list) {
    int count;

    count = list->_count;
    if (count < list->_capacity) {
        List_Reserve((igDataList *)list, count, 1);
    }
}

void igCharList_TrimCapacity(igCharList *list) {
    int count;

    count = list->_count;
    if (count < list->_capacity) {
        List_Reserve((igDataList *)list, count, 1);
    }
}

void igIntList_TrimCapacity(igIntList *self) {
    int count;

    count = self->_count;
    if (count < self->_capacity) {
        List_Reserve((igDataList *)self, count, 4);
    }
}

void igUnsignedShortList_TrimCapacity(igDataList *list) {
    int count;

    count = list->_count;
    if (count < list->_capacity) {
        List_Reserve((igDataList *)list, count, 2);
    }
}

void igShortList_TrimCapacity(igDataList *list) {
    int count;

    count = list->_count;
    if (count < list->_capacity) {
        List_Reserve((igDataList *)list, count, 2);
    }
}

void igUnsignedCharList_TrimCapacity(igDataList *list) {
    int count;

    count = list->_count;
    if (count < list->_capacity) {
        List_Reserve((igDataList *)list, count, 1);
    }
}

void igFloatList_TrimCapacity(igDataList *list) {
    int count;

    count = list->_count;
    if (count < list->_capacity) {
        List_Reserve((igDataList *)list, count, 4);
    }
}

void igPointerList_TrimCapacity(igDataList *list) {
    int count;

    count = list->_count;
    if (count < list->_capacity) {
        List_Reserve((igDataList *)list, count, 4);
    }
}

void igDependencyList_TrimCapacity(igDependencyList *self) {
    int count;

    count = self->_count;
    if (count < self->_capacity) {
        List_Reserve((igDataList *)self, count, 8);
    }
}

