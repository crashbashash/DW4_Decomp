igMetaObject *FUN_002c7d40(void) {
    if (g_igDependencyList_metaObject[0] == 0) {
        g_igDependencyList_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igDependencyList_metaObject[0];
}

igMetaObject *igDependencyList_GetMetaObject(void)
{
    igMetaObject *g = g_igDependencyList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002c7e20();
    return g_igDependencyList_metaObject[0];
}

int igDependencyList_GetVTable(void) {
    int obj[8];
    igObject_InitHeader((igObject *)obj);
    obj[0] = (int)&DAT_00532360[0];
    return *(int *)((char *)obj + *(int *)((char *)((void * *)g_objectSystem)[0] + 916));
}

void FUN_002c7e20(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igDependencyList_Register);
}

void igDependencyList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igDependencyList_metaObject),
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igDependencyList_GetMetaObject,
        igDependencyList_className,
        0x14, /* instance size */
        igDependencyList_GetVTable,
        FUN_002c7eb0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igDependencyList_GetMetaObject(void) {
    igDependencyList_GetMetaObject();
}

void FUN_002c7eb0(void) {
    int temp_s2;
    void **temp_v0;
    void *temp_s0;
    void *temp_s1;

    temp_s1 = (void *)(((void * *)g_igDependencyList_metaObject)[0]);
    temp_v0 = (void **)(((void **)igMetaObject_FindFieldByName((igMetaObject *)temp_s1, data)));
    temp_s2 = ObjectPointerList_FindIndex((char *)(*(int *)((char *)(temp_s1) + 40)), (int)temp_v0);
    temp_s0 = (void *)(((igObjectDispatchView *)(temp_v0))->cloneViaMetadata((int)(1)));
    *(int *)((char *)(temp_s0) + 60) = FUN_002c81f0();
    *(int *)((char *)(temp_s0) + 56) = 0;
    *(int *)((char *)(temp_s0) + 28) = (int)(&DAT_00586770[0]);
    igMetaObject_FinalizeAndReplaceField((igMetaObject *)temp_s1, temp_s2, (igMetaField *)temp_s0);
    *(int *)((char *)(temp_s0) + 4) = (int)((int) (*(int *)((char *)(temp_s0) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_s0) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_s0);
    }
}

