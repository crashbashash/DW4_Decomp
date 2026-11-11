igMetaObject *igNonRefCountedObjectStack_GetMetaObject(void)
{
    igMetaObject *g = g_igNonRefCountedObjectStack_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001e4430();
    return g_igNonRefCountedObjectStack_metaObject[0];
}

int igNonRefCountedObjectStack_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00524fe0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_001e4430(void)
{
    igMetaObject_RunStaticInit(igNonRefCountedObjectStack_Register);
}

void igNonRefCountedObjectStack_Register(void) {
    DataPumpLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igNonRefCountedObjectStack_metaObject,
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igNonRefCountedObjectStack_GetMetaObject,
        igNonRefCountedObjectStack_className,
        0x14, /* instance size */
        igNonRefCountedObjectStack_GetVTable,
        &igNonRefCountedObjectStack_InitFields_001e44c0[0], /* Field adder. */
        0,                                                  /* extra callback-vector item (none) */
        0                                                   /* zero-terminated callback-vector item list (none) */
    );
}

void thunk_igNonRefCountedObjectStack_GetMetaObject(void) {
    igNonRefCountedObjectStack_GetMetaObject();
}

void FUN_001e44c0(void) {
    int temp_s2;
    void **temp_v0;
    void *temp_s0;
    void *temp_s1;

    temp_s1 = (void *)(DAT_00562b78[0]);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, &DAT_004e48c8[0]));
    temp_s2 = ObjectPointerList_FindIndex(*(int *)((char *)(temp_s1) + 40), temp_v0);
    temp_s0 = (void *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    *(int *)((char *)(temp_s0) + 60) = igObjectRefMetaField_GetDefaultDescriptor();
    *(int *)((char *)(temp_s0) + 56) = 0;
    *(char *)((char *)(temp_s0) + 66) = 0;
    *(int *)((char *)(temp_s0) + 28) = (int)(&DAT_00562b80[0]);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s2, temp_s0);
    *(int *)((char *)(temp_s0) + 4) = (int)((int) (*(int *)((char *)(temp_s0) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_s0) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_s0);
    }
}

