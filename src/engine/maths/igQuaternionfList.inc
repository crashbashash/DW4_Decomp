igMetaObject *g_igQuaternionfList_metaObject;
int g_igQuaternionfList_externalStorage;

igQuaternionfList *igQuaternionfList_Create(igMemoryPoolView *pool) {
    igQuaternionfList_EnsureRegistered();
    return (igQuaternionfList *)igMetaObject_CreateInstance(g_igQuaternionfList_metaObject, pool);
}

igMetaObject *igQuaternionfList_GetOrCreateMetaObject(void) {
    if (g_igQuaternionfList_metaObject == 0) {
        g_igQuaternionfList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igQuaternionfList_metaObject;
}

igMetaObject *igQuaternionfList_GetMetaObject(void)
{
    igMetaObject *g = g_igQuaternionfList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igQuaternionfList_EnsureRegistered();
    return g_igQuaternionfList_metaObject;
}

int igQuaternionfList_GetVTable(void) {
    int tmp[8];
    int off;
    igObject_InitHeader((igObject *)&tmp[0]);
    tmp[0] = (int)&g_igQuaternionfList_vtable[0];
    off = g_objectSystem->vtableProbeOffset;
    return *(int *)((char *)tmp + off);
}

void igQuaternionfList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igQuaternionfList_Register);
}

CallbackArray *igQuaternionfList_Register(void) {
    FUN_00186a40();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igQuaternionfList_metaObject,
        Gap::Core::igDataList::arkRegisterInternal,
        Gap::Core::igDataList::getClassMeta,
        igQuaternionfList_GetMetaObjectFunction,
        "igQuaternionfList",
        0x14, /* instance size */
        igQuaternionfList_GetVTable,
        (igMetaObjectCallback)&igQuaternionfList_InitFields_00189d80[0], /* Field adder. */
        0,                                         /* extra callback-vector item (none) */
        0                                          /* zero-terminated callback-vector item list (none) */
    );
}

void igQuaternionfList_GetMetaObjectFunction(void) {
    igQuaternionfList_GetMetaObject();
}

void FUN_00189d80(void) {
    int temp_s2;
    void **temp_v0;
    void *temp_s0;
    void *temp_s1;

    temp_s1 = (void *)(g_igQuaternionfList_metaObject);
    temp_v0 = (void **)(igMetaObject_FindFieldByName((igMetaObject *)temp_s1, "_data"));
    temp_s2 = ((Gap::Core::__internalNonRefCountedObjectList *)(*(int *)((char *)(temp_s1) + 40)))->find((Gap::Core::igObject *)temp_v0);
    temp_s0 = (void *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    *(int *)((char *)(temp_s0) + 60) = (int)Gap::Math::igVec4fMetaField::getMetaField();
    *(int *)((char *)(temp_s0) + 56) = 0;
    *(int *)((char *)(temp_s0) + 28) = (int)(&g_igQuaternionfList_externalStorage);
    igMetaObject_FinalizeAndReplaceField((igMetaObject *)temp_s1, temp_s2, (igMetaField *)temp_s0);
    *(int *)((char *)(temp_s0) + 4) = (int)((int) (*(int *)((char *)(temp_s0) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_s0) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy((igObject *)temp_s0);
    }
}

