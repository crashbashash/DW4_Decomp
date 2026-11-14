void * igPointerList_Create(int arg0) {
    igPointerList_EnsureRegistered();
    return (void *)(igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x5867E0), (igMemoryPoolView *)arg0));
}

igMetaObject *igPointerList_GetOrCreateMetaObject(void) {
    if (g_igPointerList_metaObject[0] == 0) {
        g_igPointerList_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igPointerList_metaObject[0];
}

igMetaObject *igPointerList_GetMetaObject(void)
{
    igMetaObject *g = g_igPointerList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igPointerList_EnsureRegistered();
    return g_igPointerList_metaObject[0];
}

int igPointerList_GetVTable(void) {
    igPointerList list;

    igObject_InitHeader((igObject *)&list);
    list._vtable = (int)&DAT_00531ef0[0];
    return *(int *)((char *)&list + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
}

void igPointerList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igPointerList_Register);
}

void igPointerList_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igPointerList_metaObject),
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        igPointerList_GetMetaObjectFunction,
        igPointerList_className,
        0x14, /* instance size */
        igPointerList_GetVTable,
        &igPointerList_InitFields_002c92e0[0], /* Field adder. */
        0,                                     /* extra callback-vector item (none) */
        0                                      /* zero-terminated callback-vector item list (none) */
    );
}

void igPointerList_GetMetaObjectFunction(void) {
    igPointerList_GetMetaObject();
}

void igPointerList_InitFields(void) {
    int temp_s2;
    void **temp_v0;
    void *temp_s0;
    void *temp_s1;

    temp_s1 = (void *)(((void * *)g_igPointerList_metaObject)[0]);
    temp_v0 = (void **)(((void **)igMetaObject_FindFieldByName((igMetaObject *)temp_s1, data)));
    temp_s2 = ObjectPointerList_FindIndex((char *)(*(int *)((char *)(temp_s1) + 40)), (int)temp_v0);
    temp_s0 = (void *)(((igObjectDispatchView *)(temp_v0))->cloneViaMetadata((int)(1)));
    *(int *)((char *)(temp_s0) + 60) = igRawRefMetaField_GetDefaultDescriptor();
    *(int *)((char *)(temp_s0) + 56) = 0;
    *(int *)((char *)(temp_s0) + 28) = (int)(&DAT_005867e8[0]);
    igMetaObject_FinalizeAndReplaceField((igMetaObject *)temp_s1, temp_s2, (igMetaField *)temp_s0);
    *(int *)((char *)(temp_s0) + 4) = (int)((int) (*(int *)((char *)(temp_s0) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_s0) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_s0);
    }
}

