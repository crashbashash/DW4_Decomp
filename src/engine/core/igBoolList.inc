void igBoolList_Create(int arg0) {
    igBoolList_EnsureRegistered();
    igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x5868A8), (igMemoryPoolView *)arg0);
}

igMetaObject *igBoolList_GetOrCreateMetaObject(void) {
    if (g_igBoolList_metaObject[0] == 0) {
        g_igBoolList_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igBoolList_metaObject[0];
}

igMetaObject *igBoolList_GetMetaObject(void)
{
    igMetaObject *g = g_igBoolList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igBoolList_EnsureRegistered();
    return g_igBoolList_metaObject[0];
}

int igBoolList_GetVTable(void) {
    igBoolList list;

    igObject_InitHeader((igObject *)&list);
    list._vtable = (int)&DAT_005319f0[0];
    return *(int *)((char *)&list + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
}

void igBoolList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igBoolList_Register);
}

void igBoolList_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igBoolList_metaObject),
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        igBoolList_GetMetaObjectFunction,
        igBoolList_className,
        0x14, /* instance size */
        igBoolList_GetVTable,
        igBoolList_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igBoolList_GetMetaObjectFunction(void) {
    igBoolList_GetMetaObject();
}

void igBoolList_InitFields(void) {
    int temp_s2;
    void **temp_v0;
    void *temp_s0;
    void *temp_s1;

    temp_s1 = (void *)(((void * *)g_igBoolList_metaObject)[0]);
    temp_v0 = (void **)(((void **)igMetaObject_FindFieldByName((igMetaObject *)temp_s1, data)));
    temp_s2 = ObjectPointerList_FindIndex((char *)(*(int *)((char *)(temp_s1) + 40)), (int)temp_v0);
    temp_s0 = (void *)(((igObjectDispatchView *)(temp_v0))->cloneViaMetadata((int)(1)));
    *(int *)((char *)(temp_s0) + 60) = igBoolMetaField_GetDefaultDescriptor();
    *(int *)((char *)(temp_s0) + 56) = 0;
    *(int *)((char *)(temp_s0) + 28) = (int)(&DAT_005868b0[0]);
    igMetaObject_FinalizeAndReplaceField((igMetaObject *)temp_s1, temp_s2, (igMetaField *)temp_s0);
    *(int *)((char *)(temp_s0) + 4) = (int)((int) (*(int *)((char *)(temp_s0) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_s0) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_s0);
    }
}

