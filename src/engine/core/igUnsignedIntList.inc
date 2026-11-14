void igUnsignedIntList_Create(int arg0) {
    igUnsignedIntList_EnsureRegistered();
    igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x586858), (igMemoryPoolView *)arg0);
}

igMetaObject *igUnsignedIntList_GetOrCreateMetaObject(void) {
    if (g_igUnsignedIntList_metaObject[0] == 0) {
        g_igUnsignedIntList_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igUnsignedIntList_metaObject[0];
}

igMetaObject *igUnsignedIntList_GetMetaObject(void)
{
    igMetaObject *g = g_igUnsignedIntList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igUnsignedIntList_EnsureRegistered();
    return g_igUnsignedIntList_metaObject[0];
}

int igUnsignedIntList_GetVTable(void) {
    igUnsignedIntList list;

    igObject_InitHeader((igObject *)&list);
    list._vtable = (int)&DAT_0052a3a0[0];
    return *(int *)((char *)&list + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
}

void igUnsignedIntList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igUnsignedIntList_Register);
}

void igUnsignedIntList_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igUnsignedIntList_metaObject),
        igDataList_Register,                       /* base class registrar (igDataList) */
        igDataList_GetPublishedMetaObject,
        igUnsignedIntList_GetMetaObjectFunction,
        igUnsignedIntList_className,
        0x14, /* instance size */
        igUnsignedIntList_GetVTable,
        &igUnsignedIntList_InitFields_002ca5c0[0], /* field adder (class InitFields) */
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igUnsignedIntList_GetMetaObjectFunction(void) {
    igUnsignedIntList_GetMetaObject();
}

void igUnsignedIntList_InitFields(void) {
    int temp_s2;
    void **temp_v0;
    void *temp_s0;
    void *temp_s1;

    temp_s1 = (void *)(((void * *)g_igUnsignedIntList_metaObject)[0]);
    temp_v0 = (void **)(((void **)igMetaObject_FindFieldByName((igMetaObject *)temp_s1, data)));
    temp_s2 = ObjectPointerList_FindIndex((char *)(*(int *)((char *)(temp_s1) + 40)), (int)temp_v0);
    temp_s0 = (void *)(((igObjectDispatchView *)(temp_v0))->cloneViaMetadata((int)(1)));
    *(int *)((char *)(temp_s0) + 60) = igUnsignedIntMetaField_GetDefaultDescriptor();
    *(int *)((char *)(temp_s0) + 56) = 0;
    *(int *)((char *)(temp_s0) + 28) = (int)(&DAT_00586860[0]);
    igMetaObject_FinalizeAndReplaceField((igMetaObject *)temp_s1, temp_s2, (igMetaField *)temp_s0);
    *(int *)((char *)(temp_s0) + 4) = (int)((int) (*(int *)((char *)(temp_s0) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_s0) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_s0);
    }
}

