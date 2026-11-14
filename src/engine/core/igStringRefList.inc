void * igStringRefList_Create(int arg0) {
    igStringRefList_EnsureRegistered();
    return (void *)(igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x5858D8), (igMemoryPoolView *)arg0));
}

igMetaObject *igStringRefList_GetOrCreateMetaObject(void) {
    if (g_igStringRefList_metaObject[0] == 0) {
        g_igStringRefList_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igStringRefList_metaObject[0];
}

igMetaObject *igStringRefList_GetMetaObject(void)
{
    igMetaObject *g = g_igStringRefList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igStringRefList_EnsureRegistered();
    return g_igStringRefList_metaObject[0];
}

int igStringRefList_GetVTable(void) {
    igStringRefList list;

    igObject_InitHeader((igObject *)&list);
    list._vtable = (int)&DAT_0052e930[0];
    return *(int *)((char *)&list + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
}

void igStringRefList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igStringRefList_Register);
}

void igStringRefList_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igStringRefList_metaObject),
        igDataList_Register,                     /* base class registrar (igDataList) */
        igDataList_GetPublishedMetaObject,
        igStringRefList_GetMetaObjectFunction,
        igStringRefList_className,
        0x14, /* instance size */
        igStringRefList_GetVTable,
        &igStringRefList_InitFields_002b9290[0], /* field adder (class InitFields) */
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igStringRefList_GetMetaObjectFunction(void) {
    igStringRefList_GetMetaObject();
}

void igStringRefList_InitFields(void) {
    int temp_s2;
    void **temp_v0;
    void *temp_s0;
    void *temp_s1;

    temp_s1 = (void *)(((void * *)g_igStringRefList_metaObject)[0]);
    temp_v0 = (void **)(((void **)igMetaObject_FindFieldByName((igMetaObject *)temp_s1, data)));
    temp_s2 = ObjectPointerList_FindIndex((char *)(*(int *)((char *)(temp_s1) + 40)), (int)temp_v0);
    temp_s0 = (void *)(((igObjectDispatchView *)(temp_v0))->cloneViaMetadata((int)(1)));
    *(int *)((char *)(temp_s0) + 60) = igStringMetaField_GetDefaultDescriptor();
    *(int *)((char *)(temp_s0) + 56) = 0;
    *(int *)((char *)(temp_s0) + 28) = (int)(&DAT_005858e0[0]);
    igMetaObject_FinalizeAndReplaceField((igMetaObject *)temp_s1, temp_s2, (igMetaField *)temp_s0);
    *(int *)((char *)(temp_s0) + 4) = (int)((int) (*(int *)((char *)(temp_s0) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_s0) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_s0);
    }
}

