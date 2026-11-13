igMetaObject *FUN_001e4740(void) {
    if (g_igMatrixStack_metaObject[0] == 0) {
        g_igMatrixStack_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igMatrixStack_metaObject[0];
}

igMetaObject *igMatrixStack_GetMetaObject(void)
{
    igMetaObject *g = g_igMatrixStack_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001e4820();
    return g_igMatrixStack_metaObject[0];
}

int igMatrixStack_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052bd50[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_001e4820(void)
{
    igMetaObject_RunStaticInit(igMatrixStack_Register);
}

void igMatrixStack_Register(void) {
    DataPumpLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMatrixStack_metaObject,
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igMatrixStack_GetMetaObject,
        igMatrixStack_className,
        0x14, /* instance size */
        igMatrixStack_GetVTable,
        &igMatrixStack_InitFields_001e48b0[0],
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igMatrixStack_GetMetaObject(void) {
    igMatrixStack_GetMetaObject();
}

void FUN_001e48b0(void) {
    int temp_s2;
    void **temp_v0;
    void *temp_s0;
    void *temp_s1;

    temp_s1 = (void *)(g_igMatrixStack_metaObject[0]);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, &text_data_3[0]));
    temp_s2 = ObjectPointerList_FindIndex(*(int *)((char *)(temp_s1) + 40), temp_v0);
    temp_s0 = (void *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    *(int *)((char *)(temp_s0) + 60) = FUN_001888e0();
    *(int *)((char *)(temp_s0) + 56) = 0;
    *(int *)((char *)(temp_s0) + 28) = (int)(&DAT_00562ba8[0]);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s2, temp_s0);
    *(int *)((char *)(temp_s0) + 4) = (int)((int) (*(int *)((char *)(temp_s0) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_s0) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_s0);
    }
}

