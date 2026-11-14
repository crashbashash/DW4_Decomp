void igUnsignedShortList_Create(int arg0) {
    igUnsignedShortList_EnsureRegistered();
    igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x586840), (igMemoryPoolView *)arg0);
}

igMetaObject *igUnsignedShortList_GetOrCreateMetaObject(void) {
    if (g_igUnsignedShortList_metaObject[0] == 0) {
        g_igUnsignedShortList_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igUnsignedShortList_metaObject[0];
}

igMetaObject *igUnsignedShortList_GetMetaObject(void)
{
    igMetaObject *g = g_igUnsignedShortList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igUnsignedShortList_EnsureRegistered();
    return g_igUnsignedShortList_metaObject[0];
}

int igUnsignedShortList_GetVTable(void) {
    igUnsignedShortList list;

    igObject_InitHeader((igObject *)&list);
    list._vtable = (int)&DAT_00531c90[0];
    return *(int *)((char *)&list + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
}

void igUnsignedShortList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igUnsignedShortList_Register);
}

void igUnsignedShortList_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igUnsignedShortList_metaObject),
        igDataList_Register,                         /* base class registrar (igDataList) */
        igDataList_GetPublishedMetaObject,
        igUnsignedShortList_GetMetaObjectFunction,
        igUnsignedShortList_className,
        0x14, /* instance size */
        igUnsignedShortList_GetVTable,
        &igUnsignedShortList_InitFields_002ca1a0[0], /* field adder (class InitFields) */
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igUnsignedShortList_GetMetaObjectFunction(void) {
    igUnsignedShortList_GetMetaObject();
}

void igUnsignedShortList_InitFields(void) {
    int temp_s2;
    void **temp_v0;
    void *temp_s0;
    void *temp_s1;

    temp_s1 = (void *)(((void * *)g_igUnsignedShortList_metaObject)[0]);
    temp_v0 = (void **)(((void **)igMetaObject_FindFieldByName((igMetaObject *)temp_s1, data)));
    temp_s2 = ObjectPointerList_FindIndex((char *)(*(int *)((char *)(temp_s1) + 40)), (int)temp_v0);
    temp_s0 = (void *)(((igObjectDispatchView *)(temp_v0))->cloneViaMetadata((int)(1)));
    *(int *)((char *)(temp_s0) + 60) = igUnsignedShortMetaField_GetDefaultDescriptor();
    *(int *)((char *)(temp_s0) + 56) = 0;
    *(int *)((char *)(temp_s0) + 28) = (int)(&DAT_00586848[0]);
    igMetaObject_FinalizeAndReplaceField((igMetaObject *)temp_s1, temp_s2, (igMetaField *)temp_s0);
    *(int *)((char *)(temp_s0) + 4) = (int)((int) (*(int *)((char *)(temp_s0) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_s0) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_s0);
    }
}

