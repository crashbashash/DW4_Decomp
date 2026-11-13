igMetaObject *FUN_002c93a0(void) {
    if (g_igDoubleList_metaObject[0] == 0) {
        g_igDoubleList_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(g_memoryContextMetaData)));
    }
    return g_igDoubleList_metaObject[0];
}

igMetaObject *igDoubleList_GetMetaObject(void)
{
    igMetaObject *g = g_igDoubleList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002c9480();
    return g_igDoubleList_metaObject[0];
}

int igDoubleList_GetVTable(void) {
    struct Obj_2c9440 obj;

    igObject_InitHeader((struct ObjectHeader *)&obj);
    obj.vt = &DAT_0052b630[0];
    return *(int *)((char *)&obj + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
}

void FUN_002c9480(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igDoubleList_Register);
}

void igDoubleList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igDoubleList_metaObject),
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igDoubleList_GetMetaObject,
        igDoubleList_className,
        0x14, /* instance size */
        igDoubleList_GetVTable,
        FUN_002c9510,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igDoubleList_GetMetaObject(void) {
    igDoubleList_GetMetaObject();
}

void FUN_002c9510(void) {
    int temp_s2;
    void **temp_v0;
    void *temp_s0;
    void *temp_s1;

    temp_s1 = (void *)(((void * *)g_igDoubleList_metaObject)[0]);
    temp_v0 = (void **)(((void **)igMetaObject_FindFieldByName((igMetaObject *)temp_s1, data)));
    temp_s2 = ObjectPointerList_FindIndex((char *)(*(int *)((char *)(temp_s1) + 40)), (int)temp_v0);
    temp_s0 = (void *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    *(int *)((char *)(temp_s0) + 60) = FUN_002c6e20();
    *(int *)((char *)(temp_s0) + 56) = 0;
    *(int *)((char *)(temp_s0) + 28) = (int)(&DAT_005867f8[0]);
    igMetaObject_FinalizeAndReplaceField((igMetaObject *)temp_s1, temp_s2, (igMetaField *)temp_s0);
    *(int *)((char *)(temp_s0) + 4) = (int)((int) (*(int *)((char *)(temp_s0) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_s0) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_s0);
    }
}

