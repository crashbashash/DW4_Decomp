void FUN_00189e40(int arg0) {
    FUN_00189f10();
    igMetaObject_CreateInstance(*(int *)0x561098, arg0);
}

igMetaObject *igVec4ucList_GetMetaObject(void)
{
    igMetaObject *g = g_igVec4ucList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00189f10();
    return g_igVec4ucList_metaObject[0];
}

int igVec4ucList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00527910[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_00189f10(void)
{
    igMetaObject_RunStaticInit(igVec4ucList_Register);
}

void igVec4ucList_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igVec4ucList_metaObject,
        igDataList_Register,                  /* base class registrar (igDataList) */
        igDataList_GetPublishedMetaObject,
        thunk_igVec4ucList_GetMetaObject,
        igVec4ucList_className,
        0x14, /* instance size */
        igVec4ucList_GetVTable,
        &igVec4ucList_InitFields_00189fa0[0], /* field adder (class InitFields) */
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igVec4ucList_GetMetaObject(void) {
    igVec4ucList_GetMetaObject();
}

void FUN_00189fa0(void) {
    int temp_s2;
    void **temp_v0;
    void *temp_s0;
    void *temp_s1;

    temp_s1 = (void *)(g_igVec4ucList_metaObject[0]);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, &text_data_2[0]));
    temp_s2 = ObjectPointerList_FindIndex(*(int *)((char *)(temp_s1) + 40), temp_v0);
    temp_s0 = (void *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    *(int *)((char *)(temp_s0) + 60) = FUN_00187260();
    *(int *)((char *)(temp_s0) + 56) = 0;
    *(int *)((char *)(temp_s0) + 28) = (int)(&DAT_005610a0[0]);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s2, temp_s0);
    *(int *)((char *)(temp_s0) + 4) = (int)((int) (*(int *)((char *)(temp_s0) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_s0) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_s0);
    }
}

