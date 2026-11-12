void * FUN_002c9130(int arg0) {
    FUN_002c9250();
    return (void *)(igMetaObject_CreateInstance((CreateMeta *)(*(int *)0x5867E0), (MemoryPool *)arg0));
}

igMetaObject *FUN_002c9170(void) {
    if (g_igPointerList_metaObject[0] == 0) {
        g_igPointerList_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0])));
    }
    return g_igPointerList_metaObject[0];
}

igMetaObject *igPointerList_GetMetaObject(void)
{
    igMetaObject *g = g_igPointerList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002c9250();
    return g_igPointerList_metaObject[0];
}

int igPointerList_GetVTable(void) {
    struct Obj_2c9210 obj;

    igObject_InitHeader((struct ObjectHeader *)&obj);
    obj.vt = &DAT_00531ef0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
}

void FUN_002c9250(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igPointerList_Register);
}

void igPointerList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igPointerList_metaObject),
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igPointerList_GetMetaObject,
        igPointerList_className,
        0x14, /* instance size */
        igPointerList_GetVTable,
        &igPointerList_InitFields_002c92e0[0], /* Field adder. */
        0,                                     /* extra callback-vector item (none) */
        0                                      /* zero-terminated callback-vector item list (none) */
    );
}

void thunk_igPointerList_GetMetaObject(void) {
    igPointerList_GetMetaObject();
}

void FUN_002c92e0(void) {
    int temp_s2;
    void **temp_v0;
    void *temp_s0;
    void *temp_s1;

    temp_s1 = (void *)(((void * *)g_igPointerList_metaObject)[0]);
    temp_v0 = (void **)(((void **)igMetaObject_FindFieldByName((igMetaObject *)temp_s1, data)));
    temp_s2 = ObjectPointerList_FindIndex((char *)(*(int *)((char *)(temp_s1) + 40)), (int)temp_v0);
    temp_s0 = (void *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    *(int *)((char *)(temp_s0) + 60) = igRawRefMetaField_GetDefaultDescriptor();
    *(int *)((char *)(temp_s0) + 56) = 0;
    *(int *)((char *)(temp_s0) + 28) = (int)(&DAT_005867e8[0]);
    igMetaObject_FinalizeAndReplaceField((igMetaObject *)temp_s1, temp_s2, (igMetaField *)temp_s0);
    *(int *)((char *)(temp_s0) + 4) = (int)((int) (*(int *)((char *)(temp_s0) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_s0) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_s0);
    }
}

