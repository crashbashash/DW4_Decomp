int FUN_002cae50(void) {
    return DAT_00586898[0];
}

void FUN_002cae60(int arg0) {
    FUN_002caf80();
    igMetaObject_CreateInstance((CreateMeta *)(*(int *)0x586898), (MemoryPool *)arg0);
}

int FUN_002caea0(void) {
    if (DAT_00586898[0] == 0) {
        DAT_00586898[0] = ((int)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(DAT_00587040[0]))));
    }
    return DAT_00586898[0];
}

igMetaObject *igCharList_GetMetaObject(void)
{
    igMetaObject *g = g_igCharList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002caf80();
    return g_igCharList_metaObject[0];
}

int igCharList_GetVTable(void) {
    struct Obj_2caf40 obj;

    igObject_InitHeader((struct ObjectHeader *)&obj);
    obj.vt = &DAT_00531ab0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(((void * *)DAT_00586dc8)[0]) + 916));
}

void FUN_002caf80(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igCharList_Register);
}

void igCharList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igCharList_metaObject),
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igCharList_GetMetaObject,
        igCharList_className,
        0x14, /* instance size */
        igCharList_GetVTable,
        FUN_002cb010,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igCharList_GetMetaObject(void) {
    igCharList_GetMetaObject();
}

void FUN_002cb010(void) {
    int temp_s2;
    void **temp_v0;
    void *temp_s0;
    void *temp_s1;

    temp_s1 = (void *)(((void * *)DAT_00586898)[0]);
    temp_v0 = (void **)(((void **)igMetaObject_FindFieldByName((igMetaObject *)temp_s1, (const char *)&DAT_004f5eb0[0])));
    temp_s2 = ObjectPointerList_FindIndex((char *)(*(int *)((char *)(temp_s1) + 40)), (int)temp_v0);
    temp_s0 = (void *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    *(int *)((char *)(temp_s0) + 60) = FUN_002cc2c0();
    *(int *)((char *)(temp_s0) + 56) = 0;
    *(int *)((char *)(temp_s0) + 28) = (int)(&DAT_005868a0[0]);
    igMetaObject_FinalizeAndReplaceField((igMetaObject *)temp_s1, temp_s2, (igMetaField *)temp_s0);
    *(int *)((char *)(temp_s0) + 4) = (int)((int) (*(int *)((char *)(temp_s0) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_s0) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_s0);
    }
}

