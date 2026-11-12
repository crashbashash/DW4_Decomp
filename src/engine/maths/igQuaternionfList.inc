void FUN_00189bd0(int arg0) {
    FUN_00189cf0();
    igMetaObject_CreateInstance(*(int *)0x561088, arg0);
}

igMetaObject *FUN_00189c10(void) {
    if (g_igQuaternionfList_metaObject[0] == 0) {
        g_igQuaternionfList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igQuaternionfList_metaObject[0];
}

igMetaObject *igQuaternionfList_GetMetaObject(void)
{
    igMetaObject *g = g_igQuaternionfList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00189cf0();
    return g_igQuaternionfList_metaObject[0];
}

int igQuaternionfList_GetVTable(void) {
    int tmp[8];
    int off;
    igObject_InitHeader(&tmp[0]);
    tmp[0] = (int)&DAT_00527970[0];
    off = *(int *)((char *)(g_objectSystem[0]) + 916);
    return *(int *)((char *)tmp + off);
}

void FUN_00189cf0(void)
{
    igMetaObject_RunStaticInit(igQuaternionfList_Register);
}

void igQuaternionfList_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igQuaternionfList_metaObject,
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igQuaternionfList_GetMetaObject,
        igQuaternionfList_className,
        0x14, /* instance size */
        igQuaternionfList_GetVTable,
        &igQuaternionfList_InitFields_00189d80[0], /* Field adder. */
        0,                                         /* extra callback-vector item (none) */
        0                                          /* zero-terminated callback-vector item list (none) */
    );
}

void thunk_igQuaternionfList_GetMetaObject(void) {
    igQuaternionfList_GetMetaObject();
}

void FUN_00189d80(void) {
    int temp_s2;
    void **temp_v0;
    void *temp_s0;
    void *temp_s1;

    temp_s1 = (void *)(g_igQuaternionfList_metaObject[0]);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, &DAT_004e0ca0[0]));
    temp_s2 = ObjectPointerList_FindIndex(*(int *)((char *)(temp_s1) + 40), temp_v0);
    temp_s0 = (void *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    *(int *)((char *)(temp_s0) + 60) = FUN_00187520();
    *(int *)((char *)(temp_s0) + 56) = 0;
    *(int *)((char *)(temp_s0) + 28) = (int)(&DAT_00561090[0]);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s2, temp_s0);
    *(int *)((char *)(temp_s0) + 4) = (int)((int) (*(int *)((char *)(temp_s0) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_s0) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_s0);
    }
}

