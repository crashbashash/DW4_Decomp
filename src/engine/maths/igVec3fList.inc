void FUN_0018a060(int arg0) {
    FUN_0018a180();
    igMetaObject_CreateInstance(*(int *)0x5610B8, arg0);
}

igMetaObject *FUN_0018a0a0(void) {
    if (g_igVec3fList_metaObject[0] == 0) {
        g_igVec3fList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igVec3fList_metaObject[0];
}

igMetaObject *igVec3fList_GetMetaObject(void)
{
    igMetaObject *g = g_igVec3fList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0018a180();
    return g_igVec3fList_metaObject[0];
}

int igVec3fList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00524880[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_0018a180(void)
{
    igMetaObject_RunStaticInit(igVec3fList_Register);
}

void igVec3fList_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igVec3fList_metaObject,
        igDataList_Register,                 /* base class registrar (igDataList) */
        igDataList_GetPublishedMetaObject,
        thunk_igVec3fList_GetMetaObject,
        igVec3fList_className,
        0x14, /* instance size */
        igVec3fList_GetVTable,
        &igVec3fList_InitFields_0018a210[0], /* field adder (class InitFields) */
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igVec3fList_GetMetaObject(void) {
    igVec3fList_GetMetaObject();
}

void FUN_0018a210(void) {
    int temp_s2;
    void **temp_v0;
    void *temp_s0;
    void *temp_s1;

    temp_s1 = (void *)(g_igVec3fList_metaObject[0]);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, &DAT_004e0ca0[0]));
    temp_s2 = ObjectPointerList_FindIndex(*(int *)((char *)(temp_s1) + 40), temp_v0);
    temp_s0 = (void *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    *(int *)((char *)(temp_s0) + 60) = FUN_00187b10();
    *(int *)((char *)(temp_s0) + 56) = 0;
    *(int *)((char *)(temp_s0) + 28) = (int)(&DAT_005610c0[0]);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s2, temp_s0);
    *(int *)((char *)(temp_s0) + 4) = (int)((int) (*(int *)((char *)(temp_s0) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_s0) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_s0);
    }
}

