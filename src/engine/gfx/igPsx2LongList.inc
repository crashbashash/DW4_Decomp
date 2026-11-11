igMetaObject *igPsx2LongList_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2LongList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001528e0();
    return g_igPsx2LongList_metaObject[0];
}

int igPsx2LongList_GetVTable(void) {
    struct Obj_1528a0 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00526bf0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_001528e0(void)
{
    igMetaObject_RunStaticInit(igPsx2LongList_Register);
}

void igPsx2LongList_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igPsx2LongList_metaObject,
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igPsx2LongList_GetMetaObject,
        igPsx2LongList_className,
        0x14, /* instance size */
        igPsx2LongList_GetVTable,
        &igPsx2LongList_InitFields_00152970[0], /* Field adder. */
        0,                                      /* extra callback-vector item (none) */
        0                                       /* zero-terminated callback-vector item list (none) */
    );
}

void thunk_igPsx2LongList_GetMetaObject(void) {
    igPsx2LongList_GetMetaObject();
}

void FUN_00152970(void) {
    int temp_s2;
    void **temp_v0;
    void *temp_s0;
    void *temp_s1;

    temp_s1 = (void *)(DAT_005604c0[0]);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, &DAT_004db9a0[0]));
    temp_s2 = ObjectPointerList_FindIndex(*(int *)((char *)(temp_s1) + 40), temp_v0);
    temp_s0 = (void *)(((DW4VC_84_1_152970 *)(temp_v0))->vX((int)(1)));
    *(int *)((char *)(temp_s0) + 60) = FUN_002c1c70();
    *(int *)((char *)(temp_s0) + 56) = 0;
    *(int *)((char *)(temp_s0) + 28) = (int)(&DAT_005604c8[0]);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s2, temp_s0);
    *(int *)((char *)(temp_s0) + 4) = (int)((int) (*(int *)((char *)(temp_s0) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_s0) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_s0);
    }
}

