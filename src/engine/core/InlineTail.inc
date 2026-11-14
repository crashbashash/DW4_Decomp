int igPsx2IopRpcConnection_GetMeta(void)
{
    return ((int *)g_igPsx2IopRpcConnection_metaObject)[0];
}

igMetaObject *igPsx2Folder_GetMeta(void) {
    return g_igPsx2Folder_metaObject[0];
}

int igPsx2File_GetMeta(void) {
    return ((int *)g_igPsx2File_metaObject)[0];
}

void igPsx2File_InitDefaults(igPsx2File *arg0) {
    int *temp_a1;
    int temp_s0;
    int temp_v1;
    int var_v0;
    int *temp_a0;
    int *temp_s0_2;
    temp_s0 = DAT_00587330[0];
    if (g_stringPool[0] == 0) {
        var_v0 = ((int)StringPool_Allocate(0x10));
        if (var_v0 != 0) {
            var_v0 = ((int)StringPool_Construct((StringPool *)var_v0));
        }
        g_stringPool[0] = var_v0;
    }
    temp_s0_2 = (int *)(((void *)StringPool_Intern((StringPool *)g_stringPool[0], (const char *)temp_s0)));
    temp_a0 = (int *)arg0->_prefix;
    if (temp_a0 != 0) {
        temp_a1 = temp_a0 - 2;
        temp_v1 = temp_a0[-1] - 1;
        temp_a0[-1] = temp_v1;
        if (temp_v1 == 0) {
            StringChunk_ReleaseHeader((StringChunk *)(*temp_a1), (int)temp_a1);
        }
    }
    arg0->_prefix = (int)temp_s0_2;
}

int igPsx2CallStackTracer_GetMeta(void)
{
    return ((int *)g_igPsx2CallStackTracer_metaObject)[0];
}

void igUnsignedIntListNoClean_TrimCapacity(void) {

}

int igStandardQueue_GetMeta(void) {
    return ((int *)g_igStandardQueue_metaObject)[0];
}

igMetaObject *igStackMemoryPool_GetMeta(void) {
    return g_igStackMemoryPool_metaObject[0];
}

unsigned char igStackMemoryPool_IsAlchemyMemory(void *arg0) {
    return *(int *)((char *)(arg0) + 141);
}

/* igStackMemoryPool vtable slot 29 (+0x74): constant leaf returning 1. The igArenaMemoryPool and
 * igMallocMemoryPool versions return 0 and igPageMemoryPool returns 1. */
int Gap__Core__igStackMemoryPool__vfunc_29(igStackMemoryPool *self) {
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
    return ((int *)g_igProgramFile_metaObject)[0];
}

int igElfFile_GetMeta(void) {
    return ((int *)g_igElfFile_metaObject)[0];
}

igMetaObject *igVirtualCFuncMetaField_GetMeta(void) {
    return g_igVirtualCFuncMetaField_metaObject[0];
}

int igVirtualCFuncMetaField_GetDescriptor(void) {
    return ((int *)DAT_005856e0)[0];
}

int igUnsignedShortArrayMetaField_GetMeta(void) {
    return ((int *)g_igUnsignedShortArrayMetaField_metaObject)[0];
}

int igUnsignedShortArrayMetaField_GetDescriptor(void) {
    return (int)g_igUnsignedShortArrayMetaField_descriptor[0];
}

int igUnsignedLongArrayMetaField_GetMeta(void) {
    return ((int *)g_igUnsignedLongArrayMetaField_metaObject)[0];
}

int igUnsignedLongArrayMetaField_GetDescriptor(void) {
    return (int)g_igUnsignedLongArrayMetaField_descriptor[0];
}

int igUnsignedIntArrayMetaField_GetMeta(void) {
    return ((int *)g_igUnsignedIntArrayMetaField_metaObject)[0];
}

int igUnsignedIntArrayMetaField_GetDescriptor(void) {
    return (int)g_igUnsignedIntArrayMetaField_descriptor[0];
}

int igUnsignedCharMetaField_GetMeta(void) {
    return ((int *)g_igUnsignedCharMetaField_metaObject)[0];
}

int igUnsignedCharMetaField_GetDescriptor(void) {
    return (int)g_igUnsignedCharMetaField_descriptor[0];
}

int igUnsignedCharArrayMetaField_GetMeta(void) {
    return ((int *)g_igUnsignedCharArrayMetaField_metaObject)[0];
}

int igUnsignedCharArrayMetaField_GetDescriptor(void) {
    return (int)g_igUnsignedCharArrayMetaField_descriptor[0];
}

int igSymbolTable_GetMeta(void) {
    return ((int *)g_igSymbolTable_metaObject)[0];
}

int igStructMetaField_GetMeta(void) {
    return ((int *)g_igStructMetaField_metaObject)[0];
}

int igStructMetaField_GetDescriptor(void) {
    return ((int *)DAT_00585888)[0];
}

int igStringTable_GetMeta(void) {
    return ((int *)g_igStringTable_metaObject)[0];
}

igMetaObject *igStringRefList_GetMeta(void) {
    return g_igStringRefList_metaObject[0];
}

void igStringRefList_UserPreWrite(igObjectDispatchView *self)
{
    self->vfunc_16();
}

void igStringRefList_TrimCapacity(igStringRefList *l) {
    int n = l->_count;
    if (n < l->_capacity) {
        List_Reserve((igDataList *)l, n, 4);
    }
}

igMetaObject *igStringArrayMetaField_GetMeta(void) {
    return g_igStringArrayMetaField_metaObject[0];
}

int igStringArrayMetaField_GetDescriptor(void) {
    return ((int *)DAT_00585938)[0];
}

int igShortArrayMetaField_GetMeta(void) {
    return ((int *)g_igShortArrayMetaField_metaObject)[0];
}

int igShortArrayMetaField_GetDescriptor(void) {
    return (int)g_igShortArrayMetaField_descriptor[0];
}

int igResource_GetMeta(void) {
    return ((int *)g_igResource_metaObject)[0];
}

igMetaObject *igRegistry_GetMeta(void) {
    return g_igRegistry_metaObject[0];
}

int igRefMetaField_GetDescriptor(void) {
    return (int)g_igRefMetaField_descriptor[0];
}

int igRawRefArrayMetaField_GetMeta(void) {
    return ((int *)g_igRawRefArrayMetaField_metaObject)[0];
}

int igRawRefArrayMetaField_GetDescriptor(void) {
    return (int)g_igRawRefArrayMetaField_descriptor[0];
}

igMetaObject *igQueue_GetMeta(void) {
    return g_igQueue_metaObject[0];
}

int igPluginHelper_GetMeta(void) {
    return ((int *)g_igPluginHelper_metaObject)[0];
}

igMetaObject *igObjectRefArrayMetaField_GetMeta(void) {
    return g_igObjectRefArrayMetaField_metaObject[0];
}

int igObjectRefArrayMetaField_GetDescriptor(void) {
    return ((int *)DAT_00585b50)[0];
}

int igNamedObjectInfo_GetMeta(void) {
    return ((int *)g_igNamedObjectInfo_metaObject)[0];
}

igMetaObject *igMetaFieldInfo_GetMeta(void) {
    return g_igMetaFieldInfo_metaObject_00585cb8[0];
}

int igMemoryRefArrayMetaField_GetMeta(void) {
    return ((int *)g_igMemoryRefArrayMetaField_metaObject_00585de0)[0];
}

int igMemoryRefArrayMetaField_GetDescriptor(void) {
    return g_igMemoryRefArrayMetaField_metaObject_00585de8[0];
}

int igMemoryPoolInfo_GetMeta(void) {
    return ((int *)g_igMemoryPoolInfo_metaObject)[0];
}

igMetaObject *igMemoryPoolContextInfo_GetMeta(void) {
    return g_igMemoryPoolContextInfo_metaObject_00585e88[0];
}

int FUN_00331250(void) {
    return g_igMemoryPoolContextInfo_metaObject_00585e98[0];
}

int igMemoryFile_GetMeta(void) {
    return ((int *)g_igMemoryFile_metaObject)[0];
}

int igMemoryDictionary_GetMeta(void) {
    return ((int *)g_igMemoryDictionary_metaObject)[0];
}

igMetaObject *igMediaFile_GetMeta(void) {
    return g_igMediaFile_metaObject[0];
}

int igLongMetaField_GetMeta(void) {
    return ((int *)g_igLongMetaField_metaObject)[0];
}

int igLongMetaField_GetDescriptor(void) {
    return (int)g_igLongMetaField_descriptor[0];
}

int igLongArrayMetaField_GetMeta(void) {
    return ((int *)g_igLongArrayMetaField_metaObject)[0];
}

int igLongArrayMetaField_GetDescriptor(void) {
    return (int)g_igLongArrayMetaField_descriptor[0];
}

int igLocationTable_GetMeta(void) {
    return ((int *)g_igLocationTable_metaObject)[0];
}

igMetaObject *igIntArrayMetaField_GetMeta(void) {
    return g_igIntArrayMetaField_metaObject[0];
}

int igIntArrayMetaField_GetDescriptor(void) {
    return ((int *)DAT_00586110)[0];
}

int igIGBFile_GetMeta(void) {
    return ((int *)g_igIGBFile_metaObject)[0];
}

igMetaObject *igFolder_GetMeta(void) {
    return g_igFolder_metaObject[0];
}

igMetaObject *igFloatMetaField_GetMeta(void) {
    return g_igFloatMetaField_metaObject[0];
}

int igFloatMetaField_GetDescriptor(void) {
    return ((int *)DAT_00586380)[0];
}

int igFloatArrayMetaField_GetMeta(void) {
    return ((int *)g_igFloatArrayMetaField_metaObject)[0];
}

int igFloatArrayMetaField_GetDescriptor(void) {
    return (int)g_igFloatArrayMetaField_descriptor[0];
}

igMetaObject *igFile_GetMeta(void) {
    return g_igFile_metaObject[0];
}

int igExternalInfoEntry_GetMeta(void) {
    return ((int *)g_igExternalInfoEntry_metaObject)[0];
}

int igExternalIndexedEntry_GetMeta(void) {
    return ((int *)g_igExternalIndexedEntry_metaObject)[0];
}

int igExternalDirEntry_GetMeta(void) {
    return ((int *)g_igExternalDirEntry_metaObject)[0];
}

int igEventTracker_GetMeta(void) {
    return ((int *)g_igEventTracker_metaObject)[0];
}

int igEnumArrayMetaField_GetMeta(void) {
    return ((int *)g_igEnumArrayMetaField_metaObject)[0];
}

int igEnumArrayMetaField_GetDescriptor(void) {
    return (int)g_igEnumArrayMetaField_descriptor[0];
}

int igDriverDatabase_GetMeta(void) {
    return ((int *)g_igDriverDatabase_metaObject)[0];
}

igMetaObject *igDoubleMetaField_GetMeta(void) {
    return g_igDoubleMetaField_metaObject[0];
}

int igDoubleMetaField_GetDescriptor(void) {
    return ((int *)DAT_00586640)[0];
}

int igDoubleArrayMetaField_GetMeta(void) {
    return ((int *)g_igDoubleArrayMetaField_metaObject)[0];
}

int igDoubleArrayMetaField_GetDescriptor(void) {
    return (int)g_igDoubleArrayMetaField_descriptor[0];
}

int igDirectory_GetMeta(void) {
    return ((int *)g_igDirectory_metaObject)[0];
}

int igCharArrayMetaField_GetMeta(void) {
    return ((int *)g_igCharArrayMetaField_metaObject)[0];
}

int igCharArrayMetaField_GetDescriptor(void) {
    return (int)g_igCharArrayMetaField_descriptor[0];
}

int igCallStackTracer_GetMeta(void) {
    return ((int *)g_igCallStackTracer_metaObject)[0];
}

igMetaObject *igCallStackTable_GetMeta(void) {
    return g_igCallStackTable_metaObject[0];
}

igMetaObject *igBoolArrayMetaField_GetMeta(void) {
    return g_igBoolArrayMetaField_metaObject[0];
}

int igBoolArrayMetaField_GetDescriptor(void) {
    return ((int *)DAT_005869a0)[0];
}

int igMemoryDescriptorMetaField_GetMeta(void) {
    return ((int *)g_igMemoryDescriptorMetaField_metaObject)[0];
}

int igMemoryDescriptorMetaField_GetDescriptor(void) {
    return (int)g_igMemoryDescriptorMetaField_descriptor[0];
}

int igMallocMemoryPool_GetMeta(void) {
    return ((int *)g_igMallocMemoryPool_metaObject)[0];
}

void igMallocMemoryPool_ReleaseDefaults(igMemoryPoolView *self) {
    GPR_00554dbc = (GPR_00554dbc + -1);
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

int Gap__Core__igMallocMemoryPool__vfunc_29(void) {
    return 0;
}

int igArenaMemoryPool_GetMeta(void) {
    return ((int *)g_igArenaMemoryPool_metaObject)[0];
}

int igPageMemoryPool_GetMeta(void) {
    return ((int *)g_igPageMemoryPool_metaObject)[0];
}

int igAliasMemoryPool_GetMeta(void) {
    return ((int *)g_igAliasMemoryPool_metaObject)[0];
}

int Gap__Core__igAliasMemoryPool__vfunc_83(void) {
    return 1;
}

igMetaObject *igBoolMetaField_GetMeta(void) {
    return g_igBoolMetaField_metaObject[0];
}

int igBoolMetaField_GetDescriptor(void) {
    return ((int *)DAT_00586990)[0];
}

igMetaObject *igCharMetaField_GetMeta(void) {
    return g_igCharMetaField_metaObject[0];
}

int igCharMetaField_GetDescriptor(void) {
    return ((int *)DAT_00586938)[0];
}

igMetaObject *igCompoundMetaField_GetMeta(void) {
    return g_igCompoundMetaField_metaObject[0];
}

int igContextList_GetMeta(void) {
    return ((int *)g_igContextList_metaObject)[0];
}

igMetaObject *igContextExtInfo_GetMeta(void) {
    return g_igContextExtInfo_metaObject[0];
}

igMetaObject *igContextExtInfoList_GetMeta(void) {
    return g_igContextExtInfoList_metaObject[0];
}

igMetaObject *igContextExtList_GetMeta(void) {
    return g_igContextExtList_metaObject[0];
}

igMetaObject *igBoolList_GetMeta(void) {
    return g_igBoolList_metaObject[0];
}

igMetaObject *igCharListNoClean_GetMeta(void) {
    return g_igCharListNoClean_metaObject[0];
}

void igCharListNoClean_TrimCapacity(void) {

}

igMetaObject *igCharList_GetMeta(void) {
    return g_igCharList_metaObject[0];
}

igMetaObject *igIntListNoClean_GetMeta(void) {
    return g_igIntListNoClean_metaObject[0];
}

void igIntListNoClean_TrimCapacity(void) {

}

int igIntList_GetMetaObject_Virtual(void) {
    return ((int *)g_igIntList_metaObject)[0];
}

igMetaObject *igLongList_GetMeta(void) {
    return g_igLongList_metaObject[0];
}

igMetaObject *igUnsignedIntListNoClean_GetMeta(void) {
    return g_igUnsignedIntListNoClean_metaObject[0];
}

igMetaObject *igUnsignedShortList_GetMeta(void) {
    return g_igUnsignedShortList_metaObject[0];
}

igMetaObject *igShortList_GetMeta(void) {
    return g_igShortList_metaObject[0];
}

igMetaObject *igShortListList_GetMeta(void) {
    return g_igShortListList_metaObject[0];
}

int igUnsignedCharList_GetMeta(void) {
    return ((int *)g_igUnsignedCharList_metaObject)[0];
}

igMetaObject *igFloatList_GetMeta(void) {
    return g_igFloatList_metaObject[0];
}

igMetaObject *igFloatListList_GetMeta(void) {
    return g_igFloatListList_metaObject[0];
}

igMetaObject *igPointerList_GetMeta(void) {
    return g_igPointerList_metaObject[0];
}

igMetaObject *igPointerListList_GetMeta(void) {
    return g_igPointerListList_metaObject[0];
}

igMetaObject *igMetaObjectList_GetMeta(void) {
    return g_igMetaObjectList_metaObject[0];
}

igMetaObject *igMetaObjectListList_GetMeta(void) {
    return g_igMetaObjectListList_metaObject[0];
}

igMetaObject *igMetaFieldList_GetMeta(void) {
    return g_igMetaFieldList_metaObject[0];
}

igMetaObject *igIntListList_GetMeta(void) {
    return g_igIntListList_metaObject[0];
}

igMetaObject *igObjectListList_GetMeta(void) {
    return g_igObjectListList_metaObject[0];
}

igMetaObject *igStringRefListList_GetMeta(void) {
    return g_igStringRefListList_metaObject[0];
}

igMetaObject *igDependencyMetaField_GetMeta(void) {
    return g_igDependencyMetaField_metaObject[0];
}

int igDependencyMetaField_GetDescriptor(void) {
    return ((int *)DAT_00586780)[0];
}

int igDependencyList_GetMeta(void) {
    return ((int *)g_igDependencyList_metaObject)[0];
}

igMetaObject *igDirectoryList_GetMeta(void) {
    return g_igDirectoryList_metaObject[0];
}

int igEnumMetaField_GetMeta(void) {
    return ((int *)g_igEnumMetaField_metaObject)[0];
}

int igEnumMetaField_GetDescriptor(void) {
    return (int)g_igEnumMetaField_descriptor[0];
}

int igErrorHandler_GetMeta(void) {
    return ((int *)g_igErrorHandler_metaObject)[0];
}

int igInfoList_GetMeta(void) {
    return ((int *)g_igInfoList_metaObject)[0];
}

int igIntMetaField_GetMeta(void) {
    return ((int *)g_igIntMetaField_metaObject)[0];
}

int igIntMetaField_GetDescriptor(void) {
    return (int)g_igIntMetaField_descriptor[0];
}

igMetaObject *__internalNonRefCountedObjectList_GetMeta(void) {
    return g___internalNonRefCountedObjectList_metaObject[0];
}

igMetaObject *__internalObjectList_GetMeta(void) {
    return g___internalObjectList_metaObject[0];
}

int igLibraryList_GetMeta(void) {
    return ((int *)g_igLibraryList_metaObject)[0];
}

igMetaObject *igMediaList_GetMeta(void) {
    return g_igMediaList_metaObject[0];
}

igMetaObject *igMemoryFileEntry_GetMeta(void) {
    return g_igMemoryFileEntry_metaObject[0];
}

igMetaObject *igMemoryFileEntryList_GetMeta(void) {
    return g_igMemoryFileEntryList_metaObject[0];
}

igMetaObject *igMemoryPoolInfoList_GetMeta(void) {
    return g_igMemoryPoolInfoList_metaObject[0];
}

int igMemoryRefMetaField_GetMeta(void) {
    return ((int *)g_igMemoryRefMetaField_metaObject)[0];
}

int igMemoryRefMetaField_GetDescriptor(void) {
    return ((int *)DAT_00585d88)[0];
}

int igMetaEnum_GetMeta(void) {
    return ((int *)g_igMetaEnum_metaObject)[0];
}

igMetaObject *igNamedObjectList_GetMeta(void) {
    return g_igNamedObjectList_metaObject[0];
}

igMetaObject *igObjectRefMetaField_GetMeta(void) {
    return g_igObjectRefMetaField_metaObject[0];
}

int igObjectRefMetaField_GetDescriptor(void) {
    return ((int *)g_igObjectRefMetaField_descriptor)[0];
}

int igObjectStringMap_GetMeta(void) {
    return ((int *)g_igObjectStringMap_metaObject)[0];
}

int igPluginRepository_GetMeta(void) {
    return ((int *)g_igPluginRepository_metaObject)[0];
}

igMetaObject *igPluginRepositoryList_GetMeta(void) {
    return g_igPluginRepositoryList_metaObject[0];
}

int igRawRefMetaField_GetMeta(void) {
    return ((int *)g_igRawRefMetaField_metaObject)[0];
}

int igRawRefMetaField_GetDescriptor(void) {
    return (int)g_igRawRefMetaField_descriptor[0];
}

int igRegistryValue_GetMeta(void) {
    return ((int *)g_igRegistryValue_metaObject)[0];
}

igMetaObject *igRegistryValueList_GetMeta(void) {
    return g_igRegistryValueList_metaObject[0];
}

int igShortMetaField_GetMeta(void) {
    return ((int *)g_igShortMetaField_metaObject)[0];
}

int igShortMetaField_GetDescriptor(void) {
    return (int)g_igShortMetaField_descriptor[0];
}

igMetaObject *igStringMetaField_GetMeta(void) {
    return g_igStringMetaField_metaObject[0];
}

int igStringMetaField_GetDescriptor(void) {
    return ((int *)DAT_00585910)[0];
}

int igStringObj_GetMeta(void) {
    return ((int *)g_igStringObj_metaObject)[0];
}

igMetaObject *igStringObjList_GetMeta(void) {
    return g_igStringObjList_metaObject[0];
}

igMetaObject *igThreadList_GetMeta(void) {
    return g_igThreadList_metaObject[0];
}

igMetaObject *igNonRefCountedThreadList_GetMeta(void) {
    return g_igNonRefCountedThreadList_metaObject[0];
}

int igUnsignedIntMetaField_GetMeta(void) {
    return ((int *)g_igUnsignedIntMetaField_metaObject)[0];
}

int igUnsignedIntMetaField_GetDescriptor(void) {
    return (int)g_igUnsignedIntMetaField_descriptor[0];
}

igMetaObject *igUnsignedLongMetaField_GetMeta(void) {
    return g_igUnsignedLongMetaField_metaObject[0];
}

int igUnsignedLongMetaField_GetDescriptor(void) {
    return ((int *)DAT_00585718)[0];
}

igMetaObject *igUnsignedShortMetaField_GetMeta(void) {
    return g_igUnsignedShortMetaField_metaObject[0];
}

int igUnsignedShortMetaField_GetDescriptor(void) {
    return ((int *)DAT_005856f0)[0];
}

int igContextList_GetElementMeta(void) {
    return ((int *)g_igContext_metaObject)[0];
}

igMetaObject *igNonRefCountedThreadList_GetElementMeta(void) {
    return g_igThread_metaObject[0];
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

int FUN_00331a70(igTDataList<unsigned int> *arg0, unsigned int *arg1) {
    unsigned int v;
    int lo;
    int hi;
    int mid;
    unsigned int k;
    int n;
    lo = 0;
    n = arg0->_count;
    hi = n - 1;
    while (lo < hi) {
        mid = (lo + hi) >> 1;
        k = *arg1;
        v = arg0->_data[mid];
        if (v < k) {
            lo = 1 + mid;
        } else if (k < v) {
            hi = mid - 1;
        } else {
            return mid;
        }
    }
    if (!n) return 0;
    lo = (arg0->_data[lo] < *arg1) ? lo + 1 : lo;
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
    return g_igContextExt_metaObject[0];
}

igMetaObject *igContextExtInfoList_GetElementMeta(void) {
    return g_igContextExtInfo_metaObject[0];
}

igMetaObject *igMediaList_GetElementMeta(void) {
    return g_igMedia_metaObject[0];
}

igMetaObject *igMemoryFileEntryList_GetElementMeta(void) {
    return g_igMemoryFileEntry_metaObject[0];
}

igMetaObject *igMemoryPoolInfoList_GetElementMeta(void) {
    return g_igMemoryPoolInfo_metaObject[0];
}

int igInfoList_GetElementMeta(void) {
    return ((int *)g_igInfo_metaObject)[0];
}

int igPluginRepositoryList_GetElementMeta(void) {
    return ((int *)g_igPluginRepository_metaObject)[0];
}

igMetaObject *igRegistryValueList_GetElementMeta(void) {
    return g_igRegistryValue_metaObject[0];
}

igMetaObject *igDirectoryList_GetElementMeta(void) {
    return g_igDirectory_metaObject[0];
}

igMetaObject *igDirectory_GetElementMeta(void) {
    return g_igDirEntry_metaObject[0];
}

igMetaObject *igStringObjList_GetElementMeta(void) {
    return g_igStringObj_metaObject[0];
}

igMetaObject *igThreadList_GetElementMeta(void) {
    return g_igThread_metaObject[0];
}

int beDataObjList_GetElementMeta(void)
{
    return ((int *)g_igNamedObject_metaObject)[0];
}

int igLibraryList_GetElementMeta(void) {
    return ((int *)g_igLibrary_metaObject)[0];
}

igMetaObject *igStringRefListList_GetElementMeta(void) {
    return g_igStringRefList_metaObject[0];
}

igMetaObject *igObjectListList_GetElementMeta(void) {
    return g_igObjectList_metaObject[0];
}

igMetaObject *igIntListList_GetElementMeta(void) {
    return g_igIntList_metaObject[0];
}

igMetaObject *igMetaFieldList_GetElementMeta(void) {
    return g_igMetaField_metaObject[0];
}

igMetaObject *igMetaObjectListList_GetElementMeta(void) {
    return g_igMetaObjectList_metaObject[0];
}

igMetaObject *igMetaObjectList_GetElementMeta(void) {
    return g_igMetaObject_metaObject[0];
}

igMetaObject *igPointerListList_GetElementMeta(void) {
    return g_igPointerList_metaObject[0];
}

igMetaObject *igFloatListList_GetElementMeta(void) {
    return g_igFloatList_metaObject[0];
}

igMetaObject *igShortListList_GetElementMeta(void) {
    return g_igShortList_metaObject[0];
}

void igBoolList_TrimCapacity(igDataList *arg0) {
    int temp_a1;

    temp_a1 = arg0->_count;
    if (temp_a1 < arg0->_capacity) {
        List_Reserve((igDataList *)arg0, temp_a1, 1);
    }
}

void igCharList_TrimCapacity(igCharList *arg0) {
    int temp_a1;

    temp_a1 = arg0->_count;
    if (temp_a1 < arg0->_capacity) {
        List_Reserve((igDataList *)arg0, temp_a1, 1);
    }
}

void igIntList_TrimCapacity(igIntList *self) {
    int count;

    count = self->_count;
    if (count < self->_capacity) {
        List_Reserve((igDataList *)self, count, 4);
    }
}

void igUnsignedShortList_TrimCapacity(igDataList *arg0) {
    int temp_a1;

    temp_a1 = arg0->_count;
    if (temp_a1 < arg0->_capacity) {
        List_Reserve((igDataList *)arg0, temp_a1, 2);
    }
}

void igShortList_TrimCapacity(igDataList *arg0) {
    int temp_a1;

    temp_a1 = arg0->_count;
    if (temp_a1 < arg0->_capacity) {
        List_Reserve((igDataList *)arg0, temp_a1, 2);
    }
}

void igUnsignedCharList_TrimCapacity(igDataList *arg0) {
    int temp_a1;

    temp_a1 = arg0->_count;
    if (temp_a1 < arg0->_capacity) {
        List_Reserve((igDataList *)arg0, temp_a1, 1);
    }
}

void igFloatList_TrimCapacity(igDataList *arg0) {
    int temp_a1;

    temp_a1 = arg0->_count;
    if (temp_a1 < arg0->_capacity) {
        List_Reserve((igDataList *)arg0, temp_a1, 4);
    }
}

void igPointerList_TrimCapacity(igDataList *arg0) {
    int temp_a1;

    temp_a1 = arg0->_count;
    if (temp_a1 < arg0->_capacity) {
        List_Reserve((igDataList *)arg0, temp_a1, 4);
    }
}

void igDependencyList_TrimCapacity(igDependencyList *self) {
    int count;

    count = self->_count;
    if (count < self->_capacity) {
        List_Reserve((igDataList *)self, count, 8);
    }
}

