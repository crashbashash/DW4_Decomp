int Gap__Core__igPsx2IopRpcConnection__vfunc_22(void)
{
    return ((int *)g_igPsx2IopRpcConnection_metaObject)[0];
}

int Gap__Core__igPsx2Folder__vfunc_22(void) {
    return DAT_00586d68[0];
}

int Gap__Core__igPsx2File__vfunc_22(void) {
    return ((int *)DAT_00586d70)[0];
}

void Gap__Core__igPsx2File__vfunc_11(struct O_330e90 *arg0) {
    int *temp_a1;
    int temp_s0;
    int temp_v1;
    int var_v0;
    int *temp_a0;
    int *temp_s0_2;
    temp_s0 = DAT_00587330[0];
    if (DAT_00586f20[0] == 0) {
        var_v0 = ((int)FUN_002eb010(0x10));
        if (var_v0 != 0) {
            var_v0 = ((int)StringPool_Construct((S_2eadf0 *)var_v0));
        }
        DAT_00586f20[0] = var_v0;
    }
    temp_s0_2 = (int *)(((void *)StringPool_Intern((StringPool *)DAT_00586f20[0], (const char *)temp_s0)));
    temp_a0 = arg0->s;
    if (temp_a0 != 0) {
        temp_a1 = temp_a0 - 2;
        temp_v1 = temp_a0[-1] - 1;
        temp_a0[-1] = temp_v1;
        if (temp_v1 == 0) {
            StringChunk_ReleaseHeader((StringChunkOwnerView *)(*temp_a1), (int)temp_a1);
        }
    }
    arg0->s = temp_s0_2;
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

int Gap__Core__igStackMemoryPool__vfunc_22(void) {
    return DAT_00586b20[0];
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
    *status_out = g_allocatorFailureStatus[0];
}

int Gap__Core__igStackMemoryPool__vfunc_83(void) {
    return 1;
}

int Gap__Core__igProgramFile__vfunc_22(void)
{
    return ((int *)g_igProgramFile_metaObject)[0];
}

int Gap__Core__igElfFile__vfunc_22(void) {
    return ((int *)DAT_00586c00)[0];
}

int Gap__Core__igVirtualCFuncMetaField__vfunc_22(void) {
    return DAT_005856d8[0];
}

int Gap__Core__igVirtualCFuncMetaField__vfunc_23(void) {
    return ((int *)DAT_005856e0)[0];
}

int Gap__Core__igUnsignedShortArrayMetaField__vfunc_22(void) {
    return ((int *)g_igUnsignedShortArrayMetaField_metaObject)[0];
}

int Gap__Core__igUnsignedShortArrayMetaField__vfunc_23(void) {
    return g_igUnsignedShortArrayMetaField_descriptor[0];
}

int Gap__Core__igUnsignedLongArrayMetaField__vfunc_22(void) {
    return ((int *)g_igUnsignedLongArrayMetaField_metaObject)[0];
}

int Gap__Core__igUnsignedLongArrayMetaField__vfunc_23(void) {
    return g_igUnsignedLongArrayMetaField_descriptor[0];
}

int Gap__Core__igUnsignedIntArrayMetaField__vfunc_22(void) {
    return ((int *)g_igUnsignedIntArrayMetaField_metaObject)[0];
}

int Gap__Core__igUnsignedIntArrayMetaField__vfunc_23(void) {
    return g_igUnsignedIntArrayMetaField_descriptor[0];
}

int Gap__Core__igUnsignedCharMetaField__vfunc_22(void) {
    return ((int *)g_igUnsignedCharMetaField_metaObject)[0];
}

int Gap__Core__igUnsignedCharMetaField__vfunc_23(void) {
    return g_igUnsignedCharMetaField_descriptor[0];
}

int Gap__Core__igUnsignedCharArrayMetaField__vfunc_22(void) {
    return ((int *)g_igUnsignedCharArrayMetaField_metaObject)[0];
}

int Gap__Core__igUnsignedCharArrayMetaField__vfunc_23(void) {
    return g_igUnsignedCharArrayMetaField_descriptor[0];
}

int Gap__Core__igSymbolTable__vfunc_22(void) {
    return ((int *)g_igSymbolTable_metaObject)[0];
}

int Gap__Core__igStructMetaField__vfunc_22(void) {
    return ((int *)DAT_00585880)[0];
}

int Gap__Core__igStructMetaField__vfunc_23(void) {
    return ((int *)DAT_00585888)[0];
}

int Gap__Core__igStringTable__vfunc_22(void) {
    return ((int *)g_igStringTable_metaObject)[0];
}

int Gap__Core__igStringRefList__vfunc_22(void) {
    return DAT_005858d8[0];
}

void Gap__Core__igStringRefList__vfunc_14(igStringRefListView *self)
{
    self->vfunc_16();
}

void Gap__Core__igStringRefList__vfunc_18(List_3310f0 *l) {
    int n = l->count;
    if (n < l->capacity) {
        List_Reserve((L_2d6680 *)l, n, 4);
    }
}

int Gap__Core__igStringArrayMetaField__vfunc_22(void) {
    return DAT_00585930[0];
}

int Gap__Core__igStringArrayMetaField__vfunc_23(void) {
    return ((int *)DAT_00585938)[0];
}

int Gap__Core__igShortArrayMetaField__vfunc_22(void) {
    return ((int *)g_igShortArrayMetaField_metaObject)[0];
}

int Gap__Core__igShortArrayMetaField__vfunc_23(void) {
    return g_igShortArrayMetaField_descriptor[0];
}

int Gap__Core__igResource__vfunc_22(void) {
    return ((int *)g_igResource_metaObject)[0];
}

int Gap__Core__igRegistry__vfunc_22(void) {
    return DAT_00585a08[0];
}

int FUN_00331180(void) {
    return g_igRefMetaField_descriptor[0];
}

int Gap__Core__igRawRefArrayMetaField__vfunc_22(void) {
    return ((int *)g_igRawRefArrayMetaField_metaObject)[0];
}

int Gap__Core__igRawRefArrayMetaField__vfunc_23(void) {
    return g_igRawRefArrayMetaField_descriptor[0];
}

int FUN_003311b0(void) {
    return DAT_00585aa8[0];
}

int Gap__Core__igPluginHelper__vfunc_22(void) {
    return ((int *)g_igPluginHelper_metaObject)[0];
}

int Gap__Core__igObjectRefArrayMetaField__vfunc_22(void) {
    return DAT_00585b48[0];
}

int Gap__Core__igObjectRefArrayMetaField__vfunc_23(void) {
    return ((int *)DAT_00585b50)[0];
}

int Gap__Core__igNamedObjectInfo__vfunc_22(void) {
    return ((int *)g_igNamedObjectInfo_metaObject)[0];
}

int Gap__Core__igMetaFieldInfo__vfunc_22(void) {
    return DAT_00585cb8[0];
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

int Gap__Core__igMemoryPoolContextInfo__vfunc_22(void) {
    return DAT_00585e88[0];
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

int Gap__Core__igMediaFile__vfunc_22(void) {
    return DAT_00585fc8[0];
}

int Gap__Core__igLongMetaField__vfunc_22(void) {
    return ((int *)g_igLongMetaField_metaObject)[0];
}

int Gap__Core__igLongMetaField__vfunc_23(void) {
    return g_igLongMetaField_descriptor[0];
}

int Gap__Core__igLongArrayMetaField__vfunc_22(void) {
    return ((int *)g_igLongArrayMetaField_metaObject)[0];
}

int Gap__Core__igLongArrayMetaField__vfunc_23(void) {
    return g_igLongArrayMetaField_descriptor[0];
}

int Gap__Core__igLocationTable__vfunc_22(void) {
    return ((int *)g_igLocationTable_metaObject)[0];
}

int Gap__Core__igIntArrayMetaField__vfunc_22(void) {
    return DAT_00586108[0];
}

int Gap__Core__igIntArrayMetaField__vfunc_23(void) {
    return ((int *)DAT_00586110)[0];
}

int Gap__Core__igIGBFile__vfunc_22(void) {
    return ((int *)DAT_00586140)[0];
}

int Gap__Core__igFolder__vfunc_22(void) {
    return DAT_00586368[0];
}

int Gap__Core__igFloatMetaField__vfunc_22(void) {
    return DAT_00586378[0];
}

int Gap__Core__igFloatMetaField__vfunc_23(void) {
    return ((int *)DAT_00586380)[0];
}

int Gap__Core__igFloatArrayMetaField__vfunc_22(void) {
    return ((int *)g_igFloatArrayMetaField_metaObject)[0];
}

int Gap__Core__igFloatArrayMetaField__vfunc_23(void) {
    return g_igFloatArrayMetaField_descriptor[0];
}

int FUN_00331360(void) {
    return DAT_005863b0[0];
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
    return g_igEnumArrayMetaField_descriptor[0];
}

int Gap__Core__igDriverDatabase__vfunc_22(void) {
    return ((int *)g_igDriverDatabase_metaObject)[0];
}

int Gap__Core__igDoubleMetaField__vfunc_22(void) {
    return DAT_00586638[0];
}

int Gap__Core__igDoubleMetaField__vfunc_23(void) {
    return ((int *)DAT_00586640)[0];
}

int Gap__Core__igDoubleArrayMetaField__vfunc_22(void) {
    return ((int *)g_igDoubleArrayMetaField_metaObject)[0];
}

int Gap__Core__igDoubleArrayMetaField__vfunc_23(void) {
    return g_igDoubleArrayMetaField_descriptor[0];
}

int Gap__Core__igDirectory__vfunc_22(void) {
    return ((int *)g_igDirectory_metaObject)[0];
}

int Gap__Core__igCharArrayMetaField__vfunc_22(void) {
    return ((int *)g_igCharArrayMetaField_metaObject)[0];
}

int Gap__Core__igCharArrayMetaField__vfunc_23(void) {
    return g_igCharArrayMetaField_descriptor[0];
}

int Gap__Core__igCallStackTracer__vfunc_22(void) {
    return ((int *)g_igCallStackTracer_metaObject)[0];
}

int Gap__Core__igCallStackTable__vfunc_22(void) {
    return DAT_00586960[0];
}

int Gap__Core__igBoolArrayMetaField__vfunc_22(void) {
    return DAT_00586998[0];
}

int Gap__Core__igBoolArrayMetaField__vfunc_23(void) {
    return ((int *)DAT_005869a0)[0];
}

int Gap__Core__igMemoryDescriptorMetaField__vfunc_22(void) {
    return ((int *)g_igMemoryDescriptorMetaField_metaObject)[0];
}

int Gap__Core__igMemoryDescriptorMetaField__vfunc_23(void) {
    return g_igMemoryDescriptorMetaField_descriptor[0];
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
    *statusOut = g_allocatorFailureStatus[0];
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

int FUN_00331570(void) {
    return DAT_00586988[0];
}

int FUN_00331580(void) {
    return ((int *)DAT_00586990)[0];
}

int FUN_00331590(void) {
    return DAT_00586930[0];
}

int FUN_003315a0(void) {
    return ((int *)DAT_00586938)[0];
}

int FUN_003315b0(void) {
    return DAT_00586918[0];
}

int Gap__Core__igContextList__vfunc_22(void) {
    return ((int *)g_igContextList_metaObject)[0];
}

int Gap__Core__igContextExtInfo__vfunc_22(void) {
    return DAT_005868c8[0];
}

int Gap__Core__igContextExtInfoList__vfunc_22(void) {
    return DAT_005868c0[0];
}

int Gap__Core__igContextExtList__vfunc_22(void) {
    return DAT_005868b8[0];
}

int Gap__Core__igBoolList__vfunc_22(void) {
    return DAT_005868a8[0];
}

int Gap__Core__igCharListNoClean__vfunc_22(void) {
    return DAT_00586890[0];
}

void Gap__Core__igCharListNoClean__vfunc_18(void) {

}

int Gap__Core__igCharList__vfunc_22(void) {
    return DAT_00586898[0];
}

int Gap__Core__igIntListNoClean__vfunc_22(void) {
    return DAT_00586878[0];
}

void Gap__Core__igIntListNoClean__vfunc_18(void) {

}

int igIntList_GetMetaObject_Virtual(void) {
    return ((int *)g_igIntList_metaObject)[0];
}

int Gap__Core__igLongList__vfunc_22(void) {
    return DAT_00586868[0];
}

int Gap__Core__igUnsignedIntListNoClean__vfunc_22(void) {
    return DAT_00586850[0];
}

int Gap__Core__igUnsignedShortList__vfunc_22(void) {
    return DAT_00586840[0];
}

int Gap__Core__igShortList__vfunc_22(void) {
    return DAT_00586830[0];
}

int Gap__Core__igShortListList__vfunc_22(void) {
    return DAT_00586828[0];
}

int Gap__Core__igUnsignedCharList__vfunc_22(void) {
    return ((int *)DAT_00586818)[0];
}

int Gap__Core__igFloatList__vfunc_22(void) {
    return DAT_00586808[0];
}

int Gap__Core__igFloatListList__vfunc_22(void) {
    return DAT_00586800[0];
}

int Gap__Core__igPointerList__vfunc_22(void) {
    return DAT_005867e0[0];
}

int Gap__Core__igPointerListList__vfunc_22(void) {
    return DAT_005867d8[0];
}

int Gap__Core__igMetaObjectList__vfunc_22(void) {
    return DAT_005867d0[0];
}

int Gap__Core__igMetaObjectListList__vfunc_22(void) {
    return DAT_005867c8[0];
}

int Gap__Core__igMetaFieldList__vfunc_22(void) {
    return DAT_005867c0[0];
}

int Gap__Core__igIntListList__vfunc_22(void) {
    return DAT_005867b8[0];
}

int Gap__Core__igObjectListList__vfunc_22(void) {
    return DAT_005867b0[0];
}

int Gap__Core__igStringRefListList__vfunc_22(void) {
    return DAT_005867a8[0];
}

int Gap__Core__igDependencyMetaField__vfunc_22(void) {
    return DAT_00586778[0];
}

int Gap__Core__igDependencyMetaField__vfunc_23(void) {
    return ((int *)DAT_00586780)[0];
}

int Gap__Core__igDependencyList__vfunc_22(void) {
    return ((int *)g_igDependencyList_metaObject)[0];
}

int Gap__Core__igDirectoryList__vfunc_22(void) {
    return DAT_00586660[0];
}

int FUN_003317b0(void) {
    return ((int *)g_igEnumMetaField_metaObject)[0];
}

int FUN_003317c0(void) {
    return g_igEnumMetaField_descriptor[0];
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
    return g_igIntMetaField_descriptor[0];
}

int FUN_00331810(void) {
    return DAT_005860e0[0];
}

int FUN_00331820(void) {
    return DAT_005860d0[0];
}

int Gap__Core__igLibraryList__vfunc_22(void) {
    return ((int *)g_igLibraryList_metaObject)[0];
}

int Gap__Core__igMediaList__vfunc_22(void) {
    return DAT_00586018[0];
}

int Gap__Core__igMemoryFileEntry__vfunc_22(void) {
    return DAT_00585f48[0];
}

int Gap__Core__igMemoryFileEntryList__vfunc_22(void) {
    return DAT_00585f40[0];
}

int Gap__Core__igMemoryPoolInfoList__vfunc_22(void) {
    return DAT_00585df8[0];
}

int Gap__Core__igMemoryRefMetaField__vfunc_22(void) {
    return ((int *)DAT_00585d80)[0];
}

int Gap__Core__igMemoryRefMetaField__vfunc_23(void) {
    return ((int *)DAT_00585d88)[0];
}

int Gap__Core__igMetaEnum__vfunc_22(void) {
    return ((int *)g_igMetaEnum_metaObject)[0];
}

int Gap__Core__igNamedObjectList__vfunc_22(void) {
    return DAT_00585bd0[0];
}

int Gap__Core__igObjectRefMetaField__vfunc_22(void) {
    return DAT_00585b20[0];
}

int Gap__Core__igObjectRefMetaField__vfunc_23(void) {
    return ((int *)DAT_00585b28)[0];
}

int Gap__Core__igObjectStringMap__vfunc_22(void) {
    return ((int *)g_igObjectStringMap_metaObject)[0];
}

int Gap__Core__igPluginRepository__vfunc_22(void) {
    return ((int *)DAT_00585af0)[0];
}

int Gap__Core__igPluginRepositoryList__vfunc_22(void) {
    return DAT_00585ae0[0];
}

int FUN_00331910(void) {
    return ((int *)g_igRawRefMetaField_metaObject)[0];
}

int FUN_00331920(void) {
    return g_igRawRefMetaField_descriptor[0];
}

int Gap__Core__igRegistryValue__vfunc_22(void) {
    return ((int *)g_igRegistryValue_metaObject)[0];
}

int Gap__Core__igRegistryValueList__vfunc_22(void) {
    return DAT_00585a38[0];
}

int FUN_00331950(void) {
    return ((int *)g_igShortMetaField_metaObject)[0];
}

int FUN_00331960(void) {
    return g_igShortMetaField_descriptor[0];
}

int FUN_00331970(void) {
    return DAT_00585908[0];
}

int FUN_00331980(void) {
    return ((int *)DAT_00585910)[0];
}

int Gap__Core__igStringObj__vfunc_22(void) {
    return ((int *)g_igStringObj_metaObject)[0];
}

int Gap__Core__igStringObjList__vfunc_22(void) {
    return DAT_005858e8[0];
}

int Gap__Core__igThreadList__vfunc_22(void) {
    return DAT_00585828[0];
}

int Gap__Core__igNonRefCountedThreadList__vfunc_22(void) {
    return DAT_00585820[0];
}

int FUN_003319d0(void) {
    return ((int *)g_igUnsignedIntMetaField_metaObject)[0];
}

int FUN_003319e0(void) {
    return g_igUnsignedIntMetaField_descriptor[0];
}

int FUN_003319f0(void) {
    return DAT_00585710[0];
}

int FUN_00331a00(void) {
    return ((int *)DAT_00585718)[0];
}

int FUN_00331a10(void) {
    return DAT_005856e8[0];
}

int FUN_00331a20(void) {
    return ((int *)DAT_005856f0)[0];
}

int Gap__Core__igContextList__vfunc_24(void) {
    return ((int *)g_igContext_metaObject)[0];
}

int Gap__Core__igNonRefCountedThreadList__vfunc_24(void) {
    return DAT_005857c8[0];
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

int FUN_00331a70(L_331a70 *arg0, unsigned int *arg1) {
    unsigned int v;
    int lo;
    int hi;
    int mid;
    unsigned int k;
    int n;
    lo = 0;
    n = arg0->count;
    hi = n - 1;
    while (lo < hi) {
        mid = (lo + hi) >> 1;
        k = *arg1;
        v = arg0->data[mid];
        if (v < k) {
            lo = 1 + mid;
        } else if (k < v) {
            hi = mid - 1;
        } else {
            return mid;
        }
    }
    if (!n) return 0;
    lo = (arg0->data[lo] < *arg1) ? lo + 1 : lo;
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

int Gap__Core__igContextExtList__vfunc_24(void) {
    return DAT_005868e8[0];
}

int Gap__Core__igContextExtInfoList__vfunc_24(void) {
    return DAT_005868c8[0];
}

int Gap__Core__igMediaList__vfunc_24(void) {
    return DAT_00586020[0];
}

int Gap__Core__igMemoryFileEntryList__vfunc_24(void) {
    return DAT_00585f48[0];
}

int Gap__Core__igMemoryPoolInfoList__vfunc_24(void) {
    return DAT_00585e00[0];
}

int Gap__Core__igInfoList__vfunc_24(void) {
    return ((int *)g_igInfo_metaObject)[0];
}

int Gap__Core__igPluginRepositoryList__vfunc_24(void) {
    return ((int *)DAT_00585af0)[0];
}

int Gap__Core__igRegistryValueList__vfunc_24(void) {
    return DAT_00585a40[0];
}

int Gap__Core__igDirectoryList__vfunc_24(void) {
    return DAT_00586668[0];
}

int FUN_00331c20(void) {
    return DAT_00586710[0];
}

int Gap__Core__igStringObjList__vfunc_24(void) {
    return DAT_005858f0[0];
}

int Gap__Core__igThreadList__vfunc_24(void) {
    return DAT_005857c8[0];
}

int Gap__Bec__beDataObjList__vfunc_22(void)
{
    return ((int *)g_igNamedObject_metaObject)[0];
}

int Gap__Core__igLibraryList__vfunc_24(void) {
    return ((int *)g_igLibrary_metaObject)[0];
}

int Gap__Core__igStringRefListList__vfunc_24(void) {
    return DAT_005858d8[0];
}

int Gap__Core__igObjectListList__vfunc_24(void) {
    return DAT_00585b60[0];
}

int Gap__Core__igIntListList__vfunc_24(void) {
    return DAT_00586880[0];
}

int Gap__Core__igMetaFieldList__vfunc_24(void) {
    return DAT_00585cc8[0];
}

int Gap__Core__igMetaObjectListList__vfunc_24(void) {
    return DAT_005867d0[0];
}

int Gap__Core__igMetaObjectList__vfunc_24(void) {
    return DAT_00585be8[0];
}

int Gap__Core__igPointerListList__vfunc_24(void) {
    return DAT_005867e0[0];
}

int Gap__Core__igFloatListList__vfunc_24(void) {
    return DAT_00586808[0];
}

int Gap__Core__igShortListList__vfunc_24(void) {
    return DAT_00586830[0];
}

void Gap__Core__igBoolList__vfunc_18(igDataList *arg0) {
    int temp_a1;

    temp_a1 = arg0->_count;
    if (temp_a1 < arg0->_capacity) {
        List_Reserve((L_2d6680 *)arg0, temp_a1, 1);
    }
}

void Gap__Core__igCharList__vfunc_18(igCharList *arg0) {
    int temp_a1;

    temp_a1 = arg0->_count;
    if (temp_a1 < arg0->_capacity) {
        List_Reserve((L_2d6680 *)arg0, temp_a1, 1);
    }
}

void igIntList_TrimCapacity(igIntList *self) {
    int count;

    count = self->_count;
    if (count < self->_capacity) {
        List_Reserve((L_2d6680 *)self, count, 4);
    }
}

void Gap__Core__igUnsignedShortList__vfunc_18(igDataList *arg0) {
    int temp_a1;

    temp_a1 = arg0->_count;
    if (temp_a1 < arg0->_capacity) {
        List_Reserve((L_2d6680 *)arg0, temp_a1, 2);
    }
}

void Gap__Core__igShortList__vfunc_18(igDataList *arg0) {
    int temp_a1;

    temp_a1 = arg0->_count;
    if (temp_a1 < arg0->_capacity) {
        List_Reserve((L_2d6680 *)arg0, temp_a1, 2);
    }
}

void Gap__Core__igUnsignedCharList__vfunc_18(igDataList *arg0) {
    int temp_a1;

    temp_a1 = arg0->_count;
    if (temp_a1 < arg0->_capacity) {
        List_Reserve((L_2d6680 *)arg0, temp_a1, 1);
    }
}

void Gap__Core__igFloatList__vfunc_18(igDataList *arg0) {
    int temp_a1;

    temp_a1 = arg0->_count;
    if (temp_a1 < arg0->_capacity) {
        List_Reserve((L_2d6680 *)arg0, temp_a1, 4);
    }
}

void Gap__Core__igPointerList__vfunc_18(igDataList *arg0) {
    int temp_a1;

    temp_a1 = arg0->_count;
    if (temp_a1 < arg0->_capacity) {
        List_Reserve((L_2d6680 *)arg0, temp_a1, 4);
    }
}

void Gap__Core__igDependencyList__vfunc_18(igDependencyList *self) {
    int count;

    count = self->_count;
    if (count < self->_capacity) {
        List_Reserve((L_2d6680 *)self, count, 8);
    }
}

struct R_331eb0 **FUN_00331eb0(struct R_331eb0 **arg0, short arg1) {
    struct R_331eb0 *temp_a0;

    if (arg0 != 0) {
        temp_a0 = *arg0;
        if (temp_a0 != 0) {
            temp_a0->rc = temp_a0->rc - 1;
            if ((temp_a0->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        if (arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

