void FUN_002c9ff0(int arg0) {
    FUN_002ca110();
    igMetaObject_CreateInstance((CreateMeta *)(*(int *)0x586840), (MemoryPool *)arg0);
}

igMetaObject *FUN_002ca030(void) {
    if (g_igUnsignedShortList_metaObject[0] == 0) {
        g_igUnsignedShortList_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igUnsignedShortList_metaObject[0];
}

igMetaObject *igUnsignedShortList_GetMetaObject(void)
{
    igMetaObject *g = g_igUnsignedShortList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002ca110();
    return g_igUnsignedShortList_metaObject[0];
}

int igUnsignedShortList_GetVTable(void) {
    igUnsignedShortList list;

    igObject_InitHeader((struct ObjectHeader *)&list);
    list._vtable = (int)&DAT_00531c90[0];
    return *(int *)((char *)&list + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
}

void FUN_002ca110(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igUnsignedShortList_Register);
}

void igUnsignedShortList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igUnsignedShortList_metaObject),
        igDataList_Register,                         /* base class registrar (igDataList) */
        igDataList_GetPublishedMetaObject,
        thunk_igUnsignedShortList_GetMetaObject,
        igUnsignedShortList_className,
        0x14, /* instance size */
        igUnsignedShortList_GetVTable,
        &igUnsignedShortList_InitFields_002ca1a0[0], /* field adder (class InitFields) */
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igUnsignedShortList_GetMetaObject(void) {
    igUnsignedShortList_GetMetaObject();
}

void FUN_002ca1a0(void) {
    int temp_s2;
    void **temp_v0;
    void *temp_s0;
    void *temp_s1;

    temp_s1 = (void *)(((void * *)g_igUnsignedShortList_metaObject)[0]);
    temp_v0 = (void **)(((void **)igMetaObject_FindFieldByName((igMetaObject *)temp_s1, data)));
    temp_s2 = ObjectPointerList_FindIndex((char *)(*(int *)((char *)(temp_s1) + 40)), (int)temp_v0);
    temp_s0 = (void *)(((igObjectDispatchView *)(temp_v0))->cloneViaMetadata((int)(1)));
    *(int *)((char *)(temp_s0) + 60) = FUN_002b6330();
    *(int *)((char *)(temp_s0) + 56) = 0;
    *(int *)((char *)(temp_s0) + 28) = (int)(&DAT_00586848[0]);
    igMetaObject_FinalizeAndReplaceField((igMetaObject *)temp_s1, temp_s2, (igMetaField *)temp_s0);
    *(int *)((char *)(temp_s0) + 4) = (int)((int) (*(int *)((char *)(temp_s0) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_s0) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_s0);
    }
}

