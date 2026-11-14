igMetaObject *FUN_002ca680(void) {
    if (g_igLongList_metaObject[0] == 0) {
        g_igLongList_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igLongList_metaObject[0];
}

igMetaObject *igLongList_GetMetaObject(void)
{
    igMetaObject *g = g_igLongList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002ca760();
    return g_igLongList_metaObject[0];
}

int igLongList_GetVTable(void) {
    igLongList list;

    igObject_InitHeader((igObject *)&list);
    list._vtable = (int)&DAT_00531bd0[0];
    return *(int *)((char *)&list + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
}

void FUN_002ca760(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igLongList_Register);
}

void igLongList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igLongList_metaObject),
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igLongList_GetMetaObject,
        igLongList_className,
        0x14, /* instance size */
        igLongList_GetVTable,
        &igLongList_InitFields_002ca7f0[0],
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igLongList_GetMetaObject(void) {
    igLongList_GetMetaObject();
}

void FUN_002ca7f0(void) {
    int temp_s2;
    void **temp_v0;
    void *temp_s0;
    void *temp_s1;

    temp_s1 = (void *)(((void * *)g_igLongList_metaObject)[0]);
    temp_v0 = (void **)(((void **)igMetaObject_FindFieldByName((igMetaObject *)temp_s1, data)));
    temp_s2 = ObjectPointerList_FindIndex((char *)(*(int *)((char *)(temp_s1) + 40)), (int)temp_v0);
    temp_s0 = (void *)(((igObjectDispatchView *)(temp_v0))->cloneViaMetadata((int)(1)));
    *(int *)((char *)(temp_s0) + 60) = FUN_002c1c70();
    *(int *)((char *)(temp_s0) + 56) = 0;
    *(int *)((char *)(temp_s0) + 28) = (int)(&DAT_00586870[0]);
    igMetaObject_FinalizeAndReplaceField((igMetaObject *)temp_s1, temp_s2, (igMetaField *)temp_s0);
    *(int *)((char *)(temp_s0) + 4) = (int)((int) (*(int *)((char *)(temp_s0) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_s0) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_s0);
    }
}

