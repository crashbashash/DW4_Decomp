igMetaObject *g_igVec3fList_metaObject;
int g_igVec3fList_externalStorage;

igVec3fList *igVec3fList_Create(igMemoryPoolView *pool) {
    igVec3fList_EnsureRegistered();
    return (igVec3fList *)igMetaObject_CreateInstance(g_igVec3fList_metaObject, pool);
}

igMetaObject *igVec3fList_GetOrCreateMetaObject(void) {
    if (g_igVec3fList_metaObject == 0) {
        g_igVec3fList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igVec3fList_metaObject;
}

igMetaObject *igVec3fList_GetMetaObject(void)
{
    igMetaObject *g = g_igVec3fList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igVec3fList_EnsureRegistered();
    return g_igVec3fList_metaObject;
}

int igVec3fList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igVec3fList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igVec3fList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igVec3fList_Register);
}

CallbackArray *igVec3fList_Register(void) {
    FUN_00186a40();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igVec3fList_metaObject,
        igDataList_Register,                 /* base class registrar (igDataList) */
        igDataList_GetPublishedMetaObject,
        igVec3fList_GetMetaObjectFunction,
        "igVec3fList",
        0x14, /* instance size */
        igVec3fList_GetVTable,
        (igMetaObjectCallback)&igVec3fList_InitFields_0018a210[0], /* field adder (class InitFields) */
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igVec3fList_GetMetaObjectFunction(void) {
    igVec3fList_GetMetaObject();
}

void FUN_0018a210(void) {
    int temp_s2;
    void **temp_v0;
    void *temp_s0;
    void *temp_s1;

    temp_s1 = (void *)(g_igVec3fList_metaObject);
    temp_v0 = (void **)(igMetaObject_FindFieldByName((igMetaObject *)temp_s1, "_data"));
    temp_s2 = ObjectPointerList_FindIndex((__internalNonRefCountedObjectList *)(*(int *)((char *)(temp_s1) + 40)), (int)temp_v0);
    temp_s0 = (void *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    *(int *)((char *)(temp_s0) + 60) = FUN_00187b10();
    *(int *)((char *)(temp_s0) + 56) = 0;
    *(int *)((char *)(temp_s0) + 28) = (int)(&g_igVec3fList_externalStorage);
    igMetaObject_FinalizeAndReplaceField((igMetaObject *)temp_s1, temp_s2, (igMetaField *)temp_s0);
    *(int *)((char *)(temp_s0) + 4) = (int)((int) (*(int *)((char *)(temp_s0) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_s0) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy((igObject *)temp_s0);
    }
}

