void * FUN_002b90e0(int arg0) {
    FUN_002b9200();
    return (void *)(igMetaObject_CreateInstance((CreateMeta *)(*(int *)0x5858D8), (MemoryPool *)arg0));
}

int FUN_002b9120(void) {
    if (DAT_005858d8[0] == 0) {
        DAT_005858d8[0] = ((int)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(DAT_00587040[0]))));
    }
    return DAT_005858d8[0];
}

igMetaObject *igStringRefList_GetMetaObject(void)
{
    igMetaObject *g = g_igStringRefList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002b9200();
    return g_igStringRefList_metaObject[0];
}

int igStringRefList_GetVTable(void) {
    struct Obj_2b91c0 obj;

    igObject_InitHeader((struct ObjectHeader *)&obj);
    obj.vt = &DAT_0052e930[0];
    return *(int *)((char *)&obj + *(int *)((char *)(((void * *)DAT_00586dc8)[0]) + 916));
}

void FUN_002b9200(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igStringRefList_Register);
}

void igStringRefList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igStringRefList_metaObject),
        igDataList_Register,                     /* base class registrar (igDataList) */
        igDataList_GetPublishedMetaObject,
        thunk_igStringRefList_GetMetaObject,
        igStringRefList_className,
        0x14, /* instance size */
        igStringRefList_GetVTable,
        &igStringRefList_InitFields_002b9290[0], /* field adder (class InitFields) */
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igStringRefList_GetMetaObject(void) {
    igStringRefList_GetMetaObject();
}

void FUN_002b9290(void) {
    int temp_s2;
    void **temp_v0;
    void *temp_s0;
    void *temp_s1;

    temp_s1 = (void *)(((void * *)DAT_005858d8)[0]);
    temp_v0 = (void **)(((void **)igMetaObject_FindFieldByName((igMetaObject *)temp_s1, (const char *)&DAT_004f5eb0[0])));
    temp_s2 = ObjectPointerList_FindIndex((char *)(*(int *)((char *)(temp_s1) + 40)), (int)temp_v0);
    temp_s0 = (void *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    *(int *)((char *)(temp_s0) + 60) = FUN_002b9c60();
    *(int *)((char *)(temp_s0) + 56) = 0;
    *(int *)((char *)(temp_s0) + 28) = (int)(&DAT_005858e0[0]);
    igMetaObject_FinalizeAndReplaceField((igMetaObject *)temp_s1, temp_s2, (igMetaField *)temp_s0);
    *(int *)((char *)(temp_s0) + 4) = (int)((int) (*(int *)((char *)(temp_s0) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_s0) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_s0);
    }
}

