int Gap__Core__igPsx2IopRpcConnection__vfunc_22(void)
{
    return ((int *)g_igPsx2IopRpcConnection_metaObject)[0];
}

igMetaObject *Gap__Core__igPsx2Folder__vfunc_22(void) {
    return g_igPsx2Folder_metaObject[0];
}

int Gap__Core__igPsx2File__vfunc_22(void) {
    return ((int *)g_igPsx2File_metaObject)[0];
}

void Gap__Core__igPsx2File__vfunc_11(igPsx2File *arg0) {
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

int Gap__Core__igPsx2CallStackTracer__vfunc_22(void)
{
    return ((int *)g_igPsx2CallStackTracer_metaObject)[0];
}

void Gap__Core__igUnsignedIntListNoClean__vfunc_18(void) {

}

int Gap__Core__igStandardQueue__vfunc_22(void) {
    return ((int *)g_igStandardQueue_metaObject)[0];
}

igMetaObject *Gap__Core__igStackMemoryPool__vfunc_22(void) {
    return g_igStackMemoryPool_metaObject[0];
}

unsigned char Gap__Core__igStackMemoryPool__vfunc_25(void *arg0) {
    return *(int *)((char *)(arg0) + 141);
}

/* igStackMemoryPool vtable slot 29 (+0x74): constant leaf returning 1. The igArenaMemoryPool and
 * igMallocMemoryPool versions return 0 and igPageMemoryPool returns 1. */
int Gap__Core__igStackMemoryPool__vfunc_29(igStackMemoryPool *self) {
    return 1;
}

void Gap__Core__igStackMemoryPool__vfunc_41(int *status_out) {
    *status_out = g_resultFailure.v;
}

int Gap__Core__igStackMemoryPool__vfunc_83(void) {
    return 1;
}

int Gap__Core__igProgramFile__vfunc_22(void)
{
    return ((int *)g_igProgramFile_metaObject)[0];
}

int Gap__Core__igElfFile__vfunc_22(void) {
    return ((int *)g_igElfFile_metaObject)[0];
}

igMetaObject *Gap__Core__igVirtualCFuncMetaField__vfunc_22(void) {
    return g_igVirtualCFuncMetaField_metaObject[0];
}

int Gap__Core__igVirtualCFuncMetaField__vfunc_23(void) {
    return ((int *)DAT_005856e0)[0];
}

int Gap__Core__igUnsignedShortArrayMetaField__vfunc_22(void) {
    return ((int *)g_igUnsignedShortArrayMetaField_metaObject)[0];
}

int Gap__Core__igUnsignedShortArrayMetaField__vfunc_23(void) {
    return (int)g_igUnsignedShortArrayMetaField_descriptor[0];
}

int Gap__Core__igUnsignedLongArrayMetaField__vfunc_22(void) {
    return ((int *)g_igUnsignedLongArrayMetaField_metaObject)[0];
}

int Gap__Core__igUnsignedLongArrayMetaField__vfunc_23(void) {
    return (int)g_igUnsignedLongArrayMetaField_descriptor[0];
}

int Gap__Core__igUnsignedIntArrayMetaField__vfunc_22(void) {
    return ((int *)g_igUnsignedIntArrayMetaField_metaObject)[0];
}

int Gap__Core__igUnsignedIntArrayMetaField__vfunc_23(void) {
    return (int)g_igUnsignedIntArrayMetaField_descriptor[0];
}

int Gap__Core__igUnsignedCharMetaField__vfunc_22(void) {
    return ((int *)g_igUnsignedCharMetaField_metaObject)[0];
}

int Gap__Core__igUnsignedCharMetaField__vfunc_23(void) {
    return (int)g_igUnsignedCharMetaField_descriptor[0];
}

int Gap__Core__igUnsignedCharArrayMetaField__vfunc_22(void) {
    return ((int *)g_igUnsignedCharArrayMetaField_metaObject)[0];
}

int Gap__Core__igUnsignedCharArrayMetaField__vfunc_23(void) {
    return (int)g_igUnsignedCharArrayMetaField_descriptor[0];
}

int Gap__Core__igSymbolTable__vfunc_22(void) {
    return ((int *)g_igSymbolTable_metaObject)[0];
}

int Gap__Core__igStructMetaField__vfunc_22(void) {
    return ((int *)g_igStructMetaField_metaObject)[0];
}

int Gap__Core__igStructMetaField__vfunc_23(void) {
    return ((int *)DAT_00585888)[0];
}

int Gap__Core__igStringTable__vfunc_22(void) {
    return ((int *)g_igStringTable_metaObject)[0];
}

igMetaObject *Gap__Core__igStringRefList__vfunc_22(void) {
    return g_igStringRefList_metaObject[0];
}

void Gap__Core__igStringRefList__vfunc_14(igObjectDispatchView *self)
{
    self->vfunc_16();
}

void Gap__Core__igStringRefList__vfunc_18(igStringRefList *l) {
    int n = l->_count;
    if (n < l->_capacity) {
        List_Reserve((igDataList *)l, n, 4);
    }
}

igMetaObject *Gap__Core__igStringArrayMetaField__vfunc_22(void) {
    return g_igStringArrayMetaField_metaObject[0];
}

int Gap__Core__igStringArrayMetaField__vfunc_23(void) {
    return ((int *)DAT_00585938)[0];
}

int Gap__Core__igShortArrayMetaField__vfunc_22(void) {
    return ((int *)g_igShortArrayMetaField_metaObject)[0];
}

int Gap__Core__igShortArrayMetaField__vfunc_23(void) {
    return (int)g_igShortArrayMetaField_descriptor[0];
}

int Gap__Core__igResource__vfunc_22(void) {
    return ((int *)g_igResource_metaObject)[0];
}

igMetaObject *Gap__Core__igRegistry__vfunc_22(void) {
    return g_igRegistry_metaObject[0];
}

int FUN_00331180(void) {
    return (int)g_igRefMetaField_descriptor[0];
}

int Gap__Core__igRawRefArrayMetaField__vfunc_22(void) {
    return ((int *)g_igRawRefArrayMetaField_metaObject)[0];
}

int Gap__Core__igRawRefArrayMetaField__vfunc_23(void) {
    return (int)g_igRawRefArrayMetaField_descriptor[0];
}

igMetaObject *FUN_003311b0(void) {
    return g_igQueue_metaObject[0];
}

int Gap__Core__igPluginHelper__vfunc_22(void) {
    return ((int *)g_igPluginHelper_metaObject)[0];
}

igMetaObject *Gap__Core__igObjectRefArrayMetaField__vfunc_22(void) {
    return g_igObjectRefArrayMetaField_metaObject[0];
}

int Gap__Core__igObjectRefArrayMetaField__vfunc_23(void) {
    return ((int *)DAT_00585b50)[0];
}

int Gap__Core__igNamedObjectInfo__vfunc_22(void) {
    return ((int *)g_igNamedObjectInfo_metaObject)[0];
}

igMetaObject *Gap__Core__igMetaFieldInfo__vfunc_22(void) {
    return g_igMetaFieldInfo_metaObject_00585cb8[0];
}

int Gap__Core__igMemoryRefArrayMetaField__vfunc_22(void) {
    return ((int *)g_igMemoryRefArrayMetaField_metaObject_00585de0)[0];
}

int Gap__Core__igMemoryRefArrayMetaField__vfunc_23(void) {
    return g_igMemoryRefArrayMetaField_metaObject_00585de8[0];
}

int Gap__Core__igMemoryPoolInfo__vfunc_22(void) {
    return ((int *)g_igMemoryPoolInfo_metaObject)[0];
}

igMetaObject *Gap__Core__igMemoryPoolContextInfo__vfunc_22(void) {
    return g_igMemoryPoolContextInfo_metaObject_00585e88[0];
}

int FUN_00331250(void) {
    return g_igMemoryPoolContextInfo_metaObject_00585e98[0];
}

int Gap__Core__igMemoryFile__vfunc_22(void) {
    return ((int *)g_igMemoryFile_metaObject)[0];
}

int Gap__Core__igMemoryDictionary__vfunc_22(void) {
    return ((int *)g_igMemoryDictionary_metaObject)[0];
}

igMetaObject *Gap__Core__igMediaFile__vfunc_22(void) {
    return g_igMediaFile_metaObject[0];
}

int Gap__Core__igLongMetaField__vfunc_22(void) {
    return ((int *)g_igLongMetaField_metaObject)[0];
}

int Gap__Core__igLongMetaField__vfunc_23(void) {
    return (int)g_igLongMetaField_descriptor[0];
}

int Gap__Core__igLongArrayMetaField__vfunc_22(void) {
    return ((int *)g_igLongArrayMetaField_metaObject)[0];
}

int Gap__Core__igLongArrayMetaField__vfunc_23(void) {
    return (int)g_igLongArrayMetaField_descriptor[0];
}

int Gap__Core__igLocationTable__vfunc_22(void) {
    return ((int *)g_igLocationTable_metaObject)[0];
}

igMetaObject *Gap__Core__igIntArrayMetaField__vfunc_22(void) {
    return g_igIntArrayMetaField_metaObject[0];
}

int Gap__Core__igIntArrayMetaField__vfunc_23(void) {
    return ((int *)DAT_00586110)[0];
}

int Gap__Core__igIGBFile__vfunc_22(void) {
    return ((int *)g_igIGBFile_metaObject)[0];
}

igMetaObject *Gap__Core__igFolder__vfunc_22(void) {
    return g_igFolder_metaObject[0];
}

igMetaObject *Gap__Core__igFloatMetaField__vfunc_22(void) {
    return g_igFloatMetaField_metaObject[0];
}

int Gap__Core__igFloatMetaField__vfunc_23(void) {
    return ((int *)DAT_00586380)[0];
}

int Gap__Core__igFloatArrayMetaField__vfunc_22(void) {
    return ((int *)g_igFloatArrayMetaField_metaObject)[0];
}

int Gap__Core__igFloatArrayMetaField__vfunc_23(void) {
    return (int)g_igFloatArrayMetaField_descriptor[0];
}

igMetaObject *FUN_00331360(void) {
    return g_igFile_metaObject[0];
}

int Gap__Core__igExternalInfoEntry__vfunc_22(void) {
    return ((int *)g_igExternalInfoEntry_metaObject)[0];
}

int Gap__Core__igExternalIndexedEntry__vfunc_22(void) {
    return ((int *)g_igExternalIndexedEntry_metaObject)[0];
}

int Gap__Core__igExternalDirEntry__vfunc_22(void) {
    return ((int *)g_igExternalDirEntry_metaObject)[0];
}

int Gap__Core__igEventTracker__vfunc_22(void) {
    return ((int *)g_igEventTracker_metaObject)[0];
}

int Gap__Core__igEnumArrayMetaField__vfunc_22(void) {
    return ((int *)g_igEnumArrayMetaField_metaObject)[0];
}

int Gap__Core__igEnumArrayMetaField__vfunc_23(void) {
    return (int)g_igEnumArrayMetaField_descriptor[0];
}

int Gap__Core__igDriverDatabase__vfunc_22(void) {
    return ((int *)g_igDriverDatabase_metaObject)[0];
}

igMetaObject *Gap__Core__igDoubleMetaField__vfunc_22(void) {
    return g_igDoubleMetaField_metaObject[0];
}

int Gap__Core__igDoubleMetaField__vfunc_23(void) {
    return ((int *)DAT_00586640)[0];
}

int Gap__Core__igDoubleArrayMetaField__vfunc_22(void) {
    return ((int *)g_igDoubleArrayMetaField_metaObject)[0];
}

int Gap__Core__igDoubleArrayMetaField__vfunc_23(void) {
    return (int)g_igDoubleArrayMetaField_descriptor[0];
}

int Gap__Core__igDirectory__vfunc_22(void) {
    return ((int *)g_igDirectory_metaObject)[0];
}

int Gap__Core__igCharArrayMetaField__vfunc_22(void) {
    return ((int *)g_igCharArrayMetaField_metaObject)[0];
}

int Gap__Core__igCharArrayMetaField__vfunc_23(void) {
    return (int)g_igCharArrayMetaField_descriptor[0];
}

int Gap__Core__igCallStackTracer__vfunc_22(void) {
    return ((int *)g_igCallStackTracer_metaObject)[0];
}

igMetaObject *Gap__Core__igCallStackTable__vfunc_22(void) {
    return g_igCallStackTable_metaObject[0];
}

igMetaObject *Gap__Core__igBoolArrayMetaField__vfunc_22(void) {
    return g_igBoolArrayMetaField_metaObject[0];
}

int Gap__Core__igBoolArrayMetaField__vfunc_23(void) {
    return ((int *)DAT_005869a0)[0];
}

int Gap__Core__igMemoryDescriptorMetaField__vfunc_22(void) {
    return ((int *)g_igMemoryDescriptorMetaField_metaObject)[0];
}

int Gap__Core__igMemoryDescriptorMetaField__vfunc_23(void) {
    return (int)g_igMemoryDescriptorMetaField_descriptor[0];
}

int Gap__Core__igMallocMemoryPool__vfunc_22(void) {
    return ((int *)g_igMallocMemoryPool_metaObject)[0];
}

void Gap__Core__igMallocMemoryPool__vfunc_12(void) {
    GPR_00554dbc = (GPR_00554dbc + -1);
    thunk_FUN_002f0460();
}

void Gap__Core__igMallocMemoryPool__vfunc_31(void) {

}

/* Deactivates the pool: clears the reflected _isActive flag (igBoolMetaField, +112). */
void Gap__Core__igMallocMemoryPool__vfunc_32(igMallocMemoryPool *self) {
    self->_isActive = 0;
}

void Gap__Core__igMallocMemoryPool__vfunc_24(int *statusOut) {
    *statusOut = g_resultFailure.v;
}

int Gap__Core__igMallocMemoryPool__vfunc_25(void) {
    return 0;
}

int Gap__Core__igMallocMemoryPool__vfunc_26(void) {
    return 0;
}

int Gap__Core__igMallocMemoryPool__vfunc_29(void) {
    return 0;
}

int Gap__Core__igArenaMemoryPool__vfunc_22(void) {
    return ((int *)g_igArenaMemoryPool_metaObject)[0];
}

int Gap__Core__igPageMemoryPool__vfunc_22(void) {
    return ((int *)g_igPageMemoryPool_metaObject)[0];
}

int Gap__Core__igAliasMemoryPool__vfunc_22(void) {
    return ((int *)g_igAliasMemoryPool_metaObject)[0];
}

int Gap__Core__igAliasMemoryPool__vfunc_83(void) {
    return 1;
}

igMetaObject *FUN_00331570(void) {
    return g_igBoolMetaField_metaObject[0];
}

int FUN_00331580(void) {
    return ((int *)DAT_00586990)[0];
}

igMetaObject *FUN_00331590(void) {
    return g_igCharMetaField_metaObject[0];
}

int FUN_003315a0(void) {
    return ((int *)DAT_00586938)[0];
}

igMetaObject *FUN_003315b0(void) {
    return g_igCompoundMetaField_metaObject[0];
}

int Gap__Core__igContextList__vfunc_22(void) {
    return ((int *)g_igContextList_metaObject)[0];
}

igMetaObject *Gap__Core__igContextExtInfo__vfunc_22(void) {
    return g_igContextExtInfo_metaObject[0];
}

igMetaObject *Gap__Core__igContextExtInfoList__vfunc_22(void) {
    return g_igContextExtInfoList_metaObject[0];
}

igMetaObject *Gap__Core__igContextExtList__vfunc_22(void) {
    return g_igContextExtList_metaObject[0];
}

igMetaObject *Gap__Core__igBoolList__vfunc_22(void) {
    return g_igBoolList_metaObject[0];
}

igMetaObject *Gap__Core__igCharListNoClean__vfunc_22(void) {
    return g_igCharListNoClean_metaObject[0];
}

void Gap__Core__igCharListNoClean__vfunc_18(void) {

}

igMetaObject *Gap__Core__igCharList__vfunc_22(void) {
    return g_igCharList_metaObject[0];
}

igMetaObject *Gap__Core__igIntListNoClean__vfunc_22(void) {
    return g_igIntListNoClean_metaObject[0];
}

void Gap__Core__igIntListNoClean__vfunc_18(void) {

}

int igIntList_GetMetaObject_Virtual(void) {
    return ((int *)g_igIntList_metaObject)[0];
}

igMetaObject *Gap__Core__igLongList__vfunc_22(void) {
    return g_igLongList_metaObject[0];
}

igMetaObject *Gap__Core__igUnsignedIntListNoClean__vfunc_22(void) {
    return g_igUnsignedIntListNoClean_metaObject[0];
}

igMetaObject *Gap__Core__igUnsignedShortList__vfunc_22(void) {
    return g_igUnsignedShortList_metaObject[0];
}

igMetaObject *Gap__Core__igShortList__vfunc_22(void) {
    return g_igShortList_metaObject[0];
}

igMetaObject *Gap__Core__igShortListList__vfunc_22(void) {
    return g_igShortListList_metaObject[0];
}

int Gap__Core__igUnsignedCharList__vfunc_22(void) {
    return ((int *)g_igUnsignedCharList_metaObject)[0];
}

igMetaObject *Gap__Core__igFloatList__vfunc_22(void) {
    return g_igFloatList_metaObject[0];
}

igMetaObject *Gap__Core__igFloatListList__vfunc_22(void) {
    return g_igFloatListList_metaObject[0];
}

igMetaObject *Gap__Core__igPointerList__vfunc_22(void) {
    return g_igPointerList_metaObject[0];
}

igMetaObject *Gap__Core__igPointerListList__vfunc_22(void) {
    return g_igPointerListList_metaObject[0];
}

igMetaObject *Gap__Core__igMetaObjectList__vfunc_22(void) {
    return g_igMetaObjectList_metaObject[0];
}

igMetaObject *Gap__Core__igMetaObjectListList__vfunc_22(void) {
    return g_igMetaObjectListList_metaObject[0];
}

igMetaObject *Gap__Core__igMetaFieldList__vfunc_22(void) {
    return g_igMetaFieldList_metaObject[0];
}

igMetaObject *Gap__Core__igIntListList__vfunc_22(void) {
    return g_igIntListList_metaObject[0];
}

igMetaObject *Gap__Core__igObjectListList__vfunc_22(void) {
    return g_igObjectListList_metaObject[0];
}

igMetaObject *Gap__Core__igStringRefListList__vfunc_22(void) {
    return g_igStringRefListList_metaObject[0];
}

igMetaObject *Gap__Core__igDependencyMetaField__vfunc_22(void) {
    return g_igDependencyMetaField_metaObject[0];
}

int Gap__Core__igDependencyMetaField__vfunc_23(void) {
    return ((int *)DAT_00586780)[0];
}

int Gap__Core__igDependencyList__vfunc_22(void) {
    return ((int *)g_igDependencyList_metaObject)[0];
}

igMetaObject *Gap__Core__igDirectoryList__vfunc_22(void) {
    return g_igDirectoryList_metaObject[0];
}

int FUN_003317b0(void) {
    return ((int *)g_igEnumMetaField_metaObject)[0];
}

int FUN_003317c0(void) {
    return (int)g_igEnumMetaField_descriptor[0];
}

int Gap__Core__igErrorHandler__vfunc_22(void) {
    return ((int *)g_igErrorHandler_metaObject)[0];
}

int Gap__Core__igInfoList__vfunc_22(void) {
    return ((int *)g_igInfoList_metaObject)[0];
}

int FUN_003317f0(void) {
    return ((int *)g_igIntMetaField_metaObject)[0];
}

int FUN_00331800(void) {
    return (int)g_igIntMetaField_descriptor[0];
}

igMetaObject *FUN_00331810(void) {
    return g___internalNonRefCountedObjectList_metaObject[0];
}

igMetaObject *FUN_00331820(void) {
    return g___internalObjectList_metaObject[0];
}

int Gap__Core__igLibraryList__vfunc_22(void) {
    return ((int *)g_igLibraryList_metaObject)[0];
}

igMetaObject *Gap__Core__igMediaList__vfunc_22(void) {
    return g_igMediaList_metaObject[0];
}

igMetaObject *Gap__Core__igMemoryFileEntry__vfunc_22(void) {
    return g_igMemoryFileEntry_metaObject[0];
}

igMetaObject *Gap__Core__igMemoryFileEntryList__vfunc_22(void) {
    return g_igMemoryFileEntryList_metaObject[0];
}

igMetaObject *Gap__Core__igMemoryPoolInfoList__vfunc_22(void) {
    return g_igMemoryPoolInfoList_metaObject[0];
}

int Gap__Core__igMemoryRefMetaField__vfunc_22(void) {
    return ((int *)g_igMemoryRefMetaField_metaObject)[0];
}

int Gap__Core__igMemoryRefMetaField__vfunc_23(void) {
    return ((int *)DAT_00585d88)[0];
}

int Gap__Core__igMetaEnum__vfunc_22(void) {
    return ((int *)g_igMetaEnum_metaObject)[0];
}

igMetaObject *Gap__Core__igNamedObjectList__vfunc_22(void) {
    return g_igNamedObjectList_metaObject[0];
}

igMetaObject *Gap__Core__igObjectRefMetaField__vfunc_22(void) {
    return g_igObjectRefMetaField_metaObject[0];
}

int Gap__Core__igObjectRefMetaField__vfunc_23(void) {
    return ((int *)g_igObjectRefMetaField_descriptor)[0];
}

int Gap__Core__igObjectStringMap__vfunc_22(void) {
    return ((int *)g_igObjectStringMap_metaObject)[0];
}

int Gap__Core__igPluginRepository__vfunc_22(void) {
    return ((int *)g_igPluginRepository_metaObject)[0];
}

igMetaObject *Gap__Core__igPluginRepositoryList__vfunc_22(void) {
    return g_igPluginRepositoryList_metaObject[0];
}

int FUN_00331910(void) {
    return ((int *)g_igRawRefMetaField_metaObject)[0];
}

int FUN_00331920(void) {
    return (int)g_igRawRefMetaField_descriptor[0];
}

int Gap__Core__igRegistryValue__vfunc_22(void) {
    return ((int *)g_igRegistryValue_metaObject)[0];
}

igMetaObject *Gap__Core__igRegistryValueList__vfunc_22(void) {
    return g_igRegistryValueList_metaObject[0];
}

int FUN_00331950(void) {
    return ((int *)g_igShortMetaField_metaObject)[0];
}

int FUN_00331960(void) {
    return (int)g_igShortMetaField_descriptor[0];
}

igMetaObject *FUN_00331970(void) {
    return g_igStringMetaField_metaObject[0];
}

int FUN_00331980(void) {
    return ((int *)DAT_00585910)[0];
}

int Gap__Core__igStringObj__vfunc_22(void) {
    return ((int *)g_igStringObj_metaObject)[0];
}

igMetaObject *Gap__Core__igStringObjList__vfunc_22(void) {
    return g_igStringObjList_metaObject[0];
}

igMetaObject *Gap__Core__igThreadList__vfunc_22(void) {
    return g_igThreadList_metaObject[0];
}

igMetaObject *Gap__Core__igNonRefCountedThreadList__vfunc_22(void) {
    return g_igNonRefCountedThreadList_metaObject[0];
}

int FUN_003319d0(void) {
    return ((int *)g_igUnsignedIntMetaField_metaObject)[0];
}

int FUN_003319e0(void) {
    return (int)g_igUnsignedIntMetaField_descriptor[0];
}

igMetaObject *FUN_003319f0(void) {
    return g_igUnsignedLongMetaField_metaObject[0];
}

int FUN_00331a00(void) {
    return ((int *)DAT_00585718)[0];
}

igMetaObject *FUN_00331a10(void) {
    return g_igUnsignedShortMetaField_metaObject[0];
}

int FUN_00331a20(void) {
    return ((int *)DAT_005856f0)[0];
}

int Gap__Core__igContextList__vfunc_24(void) {
    return ((int *)g_igContext_metaObject)[0];
}

igMetaObject *Gap__Core__igNonRefCountedThreadList__vfunc_24(void) {
    return g_igThread_metaObject[0];
}

/* Element size in bytes of the list's items: 8. The same class's TrimCapacity (vfunc_18) re-sizes
 * the buffer with List_Reserve(self, count, 8), and the sibling lists igCharMetricsList (0x28) and
 * igPsx2AudioSourceList (0x24) return their item size from this same slot 23. */
int Gap__Core__igDependencyList__vfunc_23(void) {
    return 8;
}

int Gap__Core__igPointerList__vfunc_23(void) {
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

int Gap__Core__igFloatList__vfunc_23(void) {
    return 4;
}

int Gap__Core__igUnsignedCharList__vfunc_23(void) {
    return 1;
}

int Gap__Core__igShortList__vfunc_23(void) {
    return 2;
}

int Gap__Core__igUnsignedShortList__vfunc_23(void) {
    return 2;
}

int Gap__Core__igIntList__vfunc_23(void) {
    return 4;
}

int Gap__Core__igCharList__vfunc_23(void) {
    return 1;
}

int Gap__Core__igBoolList__vfunc_23(void) {
    return 1;
}

int Gap__Core__igStringRefList__vfunc_23(void) {
    return 4;
}

igMetaObject *Gap__Core__igContextExtList__vfunc_24(void) {
    return g_igContextExt_metaObject[0];
}

igMetaObject *Gap__Core__igContextExtInfoList__vfunc_24(void) {
    return g_igContextExtInfo_metaObject[0];
}

igMetaObject *Gap__Core__igMediaList__vfunc_24(void) {
    return g_igMedia_metaObject[0];
}

igMetaObject *Gap__Core__igMemoryFileEntryList__vfunc_24(void) {
    return g_igMemoryFileEntry_metaObject[0];
}

igMetaObject *Gap__Core__igMemoryPoolInfoList__vfunc_24(void) {
    return g_igMemoryPoolInfo_metaObject[0];
}

int Gap__Core__igInfoList__vfunc_24(void) {
    return ((int *)g_igInfo_metaObject)[0];
}

int Gap__Core__igPluginRepositoryList__vfunc_24(void) {
    return ((int *)g_igPluginRepository_metaObject)[0];
}

igMetaObject *Gap__Core__igRegistryValueList__vfunc_24(void) {
    return g_igRegistryValue_metaObject[0];
}

igMetaObject *Gap__Core__igDirectoryList__vfunc_24(void) {
    return g_igDirectory_metaObject[0];
}

igMetaObject *FUN_00331c20(void) {
    return g_igDirEntry_metaObject[0];
}

igMetaObject *Gap__Core__igStringObjList__vfunc_24(void) {
    return g_igStringObj_metaObject[0];
}

igMetaObject *Gap__Core__igThreadList__vfunc_24(void) {
    return g_igThread_metaObject[0];
}

int Gap__Bec__beDataObjList__vfunc_22(void)
{
    return ((int *)g_igNamedObject_metaObject)[0];
}

int Gap__Core__igLibraryList__vfunc_24(void) {
    return ((int *)g_igLibrary_metaObject)[0];
}

igMetaObject *Gap__Core__igStringRefListList__vfunc_24(void) {
    return g_igStringRefList_metaObject[0];
}

igMetaObject *Gap__Core__igObjectListList__vfunc_24(void) {
    return g_igObjectList_metaObject[0];
}

igMetaObject *Gap__Core__igIntListList__vfunc_24(void) {
    return g_igIntList_metaObject[0];
}

igMetaObject *Gap__Core__igMetaFieldList__vfunc_24(void) {
    return g_igMetaField_metaObject[0];
}

igMetaObject *Gap__Core__igMetaObjectListList__vfunc_24(void) {
    return g_igMetaObjectList_metaObject[0];
}

igMetaObject *Gap__Core__igMetaObjectList__vfunc_24(void) {
    return g_igMetaObject_metaObject[0];
}

igMetaObject *Gap__Core__igPointerListList__vfunc_24(void) {
    return g_igPointerList_metaObject[0];
}

igMetaObject *Gap__Core__igFloatListList__vfunc_24(void) {
    return g_igFloatList_metaObject[0];
}

igMetaObject *Gap__Core__igShortListList__vfunc_24(void) {
    return g_igShortList_metaObject[0];
}

void Gap__Core__igBoolList__vfunc_18(igDataList *arg0) {
    int temp_a1;

    temp_a1 = arg0->_count;
    if (temp_a1 < arg0->_capacity) {
        List_Reserve((igDataList *)arg0, temp_a1, 1);
    }
}

void Gap__Core__igCharList__vfunc_18(igCharList *arg0) {
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

void Gap__Core__igUnsignedShortList__vfunc_18(igDataList *arg0) {
    int temp_a1;

    temp_a1 = arg0->_count;
    if (temp_a1 < arg0->_capacity) {
        List_Reserve((igDataList *)arg0, temp_a1, 2);
    }
}

void Gap__Core__igShortList__vfunc_18(igDataList *arg0) {
    int temp_a1;

    temp_a1 = arg0->_count;
    if (temp_a1 < arg0->_capacity) {
        List_Reserve((igDataList *)arg0, temp_a1, 2);
    }
}

void Gap__Core__igUnsignedCharList__vfunc_18(igDataList *arg0) {
    int temp_a1;

    temp_a1 = arg0->_count;
    if (temp_a1 < arg0->_capacity) {
        List_Reserve((igDataList *)arg0, temp_a1, 1);
    }
}

void Gap__Core__igFloatList__vfunc_18(igDataList *arg0) {
    int temp_a1;

    temp_a1 = arg0->_count;
    if (temp_a1 < arg0->_capacity) {
        List_Reserve((igDataList *)arg0, temp_a1, 4);
    }
}

void Gap__Core__igPointerList__vfunc_18(igDataList *arg0) {
    int temp_a1;

    temp_a1 = arg0->_count;
    if (temp_a1 < arg0->_capacity) {
        List_Reserve((igDataList *)arg0, temp_a1, 4);
    }
}

void Gap__Core__igDependencyList__vfunc_18(igDependencyList *self) {
    int count;

    count = self->_count;
    if (count < self->_capacity) {
        List_Reserve((igDataList *)self, count, 8);
    }
}

