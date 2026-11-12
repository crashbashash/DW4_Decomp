void FUN_0018a2d0(int arg0) {
    FUN_0018a3a0();
    igMetaObject_CreateInstance(*(int *)0x5610C8, arg0);
}

igMetaObject *igVec2fList_GetMetaObject(void)
{
    igMetaObject *g = g_igVec2fList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0018a3a0();
    return g_igVec2fList_metaObject[0];
}

int igVec2fList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_005278b0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_0018a3a0(void)
{
    igMetaObject_RunStaticInit(igVec2fList_Register);
}

void igVec2fList_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igVec2fList_metaObject,
        igDataList_Register,                 /* base class registrar (igDataList) */
        igDataList_GetPublishedMetaObject,
        thunk_igVec2fList_GetMetaObject,
        igVec2fList_className,
        0x14, /* instance size */
        igVec2fList_GetVTable,
        &igVec2fList_InitFields_0018a430[0], /* field adder (class InitFields) */
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igVec2fList_GetMetaObject(void) {
    igVec2fList_GetMetaObject();
}

void FUN_0018a430(void) {
    int temp_s2;
    void **temp_v0;
    void *temp_s0;
    void *temp_s1;

    temp_s1 = (void *)(DAT_005610c8[0]);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, &DAT_004e0ca0[0]));
    temp_s2 = ObjectPointerList_FindIndex(*(int *)((char *)(temp_s1) + 40), temp_v0);
    temp_s0 = (void *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    *(int *)((char *)(temp_s0) + 60) = FUN_00187dd0();
    *(int *)((char *)(temp_s0) + 56) = 0;
    *(int *)((char *)(temp_s0) + 28) = (int)(&DAT_005610d0[0]);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s2, temp_s0);
    *(int *)((char *)(temp_s0) + 4) = (int)((int) (*(int *)((char *)(temp_s0) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_s0) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_s0);
    }
}

