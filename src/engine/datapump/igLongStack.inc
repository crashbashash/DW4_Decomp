int FUN_001e4010(void) {
    if (DAT_00562b60[0] == 0) {
        DAT_00562b60[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_00562b60[0];
}

igMetaObject *igLongStack_GetMetaObject(void)
{
    igMetaObject *g = g_igLongStack_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001e40f0();
    return g_igLongStack_metaObject[0];
}

int igLongStack_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052bdb0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_001e40f0(void)
{
    igMetaObject_RunStaticInit(igLongStack_Register);
}

void igLongStack_Register(void) {
    DataPumpLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igLongStack_metaObject,
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igLongStack_GetMetaObject,
        igLongStack_className,
        0x14, /* instance size */
        igLongStack_GetVTable,
        &igLongStack_InitFields_001e4180[0],
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igLongStack_GetMetaObject(void) {
    igLongStack_GetMetaObject();
}

void FUN_001e4180(void) {
    int temp_s2;
    void **temp_v0;
    void *temp_s0;
    void *temp_s1;

    temp_s1 = (void *)(DAT_00562b60[0]);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, &DAT_004e48c8[0]));
    temp_s2 = ObjectPointerList_FindIndex(*(int *)((char *)(temp_s1) + 40), temp_v0);
    temp_s0 = (void *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    *(int *)((char *)(temp_s0) + 60) = FUN_002c1c70();
    *(int *)((char *)(temp_s0) + 56) = 0;
    *(int *)((char *)(temp_s0) + 28) = (int)(&DAT_00562b68[0]);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s2, temp_s0);
    *(int *)((char *)(temp_s0) + 4) = (int)((int) (*(int *)((char *)(temp_s0) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_s0) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_s0);
    }
}

