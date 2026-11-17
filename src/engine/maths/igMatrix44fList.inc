igMetaObject *g_igMatrix44fList_metaObject;
int g_igMatrix44fList_externalStorage;

igMetaObject *igMatrix44fList_GetOrCreateMetaObject(void) {
    if (g_igMatrix44fList_metaObject == 0) {
        g_igMatrix44fList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igMatrix44fList_metaObject;
}

igMetaObject *igMatrix44fList_GetMetaObject(void)
{
    igMetaObject *g = g_igMatrix44fList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igMatrix44fList_EnsureRegistered();
    return g_igMatrix44fList_metaObject;
}

int igMatrix44fList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igMatrix44fList_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
}

void igMatrix44fList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igMatrix44fList_Register);
}

CallbackArray *igMatrix44fList_Register(void) {
    FUN_00186a40();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igMatrix44fList_metaObject,
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igMatrix44fList_GetMetaObject,
        "igMatrix44fList",
        0x14, /* instance size */
        igMatrix44fList_GetVTable,
        (igMetaObjectCallback)&igMatrix44fList_InitFields_00189b10[0],
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igMatrix44fList_GetMetaObject(void) {
    igMatrix44fList_GetMetaObject();
}

void FUN_00189b10(void) {
    int temp_s2;
    void **temp_v0;
    void *temp_s0;
    void *temp_s1;

    temp_s1 = (void *)(g_igMatrix44fList_metaObject);
    temp_v0 = (void **)(igMetaObject_FindFieldByName((igMetaObject *)temp_s1, "_data"));
    temp_s2 = ObjectPointerList_FindIndex((__internalNonRefCountedObjectList *)(*(int *)((char *)(temp_s1) + 40)), (int)temp_v0);
    temp_s0 = (void *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    *(int *)((char *)(temp_s0) + 60) = FUN_001888e0();
    *(int *)((char *)(temp_s0) + 56) = 0;
    *(int *)((char *)(temp_s0) + 28) = (int)(&g_igMatrix44fList_externalStorage);
    igMetaObject_FinalizeAndReplaceField((igMetaObject *)temp_s1, temp_s2, (igMetaField *)temp_s0);
    *(int *)((char *)(temp_s0) + 4) = (int)((int) (*(int *)((char *)(temp_s0) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_s0) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy((igObject *)temp_s0);
    }
}

