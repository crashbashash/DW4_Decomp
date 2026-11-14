void igShortList_Create(int arg0) {
    igShortList_EnsureRegistered();
    igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x586830), (igMemoryPoolView *)arg0);
}

igMetaObject *igShortList_GetOrCreateMetaObject(void) {
    if (g_igShortList_metaObject[0] == 0) {
        g_igShortList_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igShortList_metaObject[0];
}

igMetaObject *igShortList_GetMetaObject(void)
{
    igMetaObject *g = g_igShortList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igShortList_EnsureRegistered();
    return g_igShortList_metaObject[0];
}

int igShortList_GetVTable(void) {
    igShortList list;

    igObject_InitHeader((igObject *)&list);
    list._vtable = (int)&DAT_00531cf0[0];
    return *(int *)((char *)&list + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
}

void igShortList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igShortList_Register);
}

void igShortList_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igShortList_metaObject),
        igDataList_Register,                 /* base class registrar (igDataList) */
        igDataList_GetPublishedMetaObject,
        igShortList_GetMetaObjectFunction,
        igShortList_className,
        0x14, /* instance size */
        igShortList_GetVTable,
        &igShortList_InitFields_002c9f30[0], /* field adder (class InitFields) */
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igShortList_GetMetaObjectFunction(void) {
    igShortList_GetMetaObject();
}

void igShortList_InitFields(void) {
    int temp_s2;
    void **temp_v0;
    void *temp_s0;
    void *temp_s1;

    temp_s1 = (void *)(((void * *)g_igShortList_metaObject)[0]);
    temp_v0 = (void **)(((void **)igMetaObject_FindFieldByName((igMetaObject *)temp_s1, data)));
    temp_s2 = ObjectPointerList_FindIndex((char *)(*(int *)((char *)(temp_s1) + 40)), (int)temp_v0);
    temp_s0 = (void *)(((igObjectDispatchView *)(temp_v0))->cloneViaMetadata((int)(1)));
    *(int *)((char *)(temp_s0) + 60) = igShortMetaField_GetDefaultDescriptor();
    *(int *)((char *)(temp_s0) + 56) = 0;
    *(int *)((char *)(temp_s0) + 28) = (int)(&DAT_00586838[0]);
    igMetaObject_FinalizeAndReplaceField((igMetaObject *)temp_s1, temp_s2, (igMetaField *)temp_s0);
    *(int *)((char *)(temp_s0) + 4) = (int)((int) (*(int *)((char *)(temp_s0) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_s0) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_s0);
    }
}

