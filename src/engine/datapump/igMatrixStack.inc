igMetaObject *g_igMatrixStack_metaObject;
igMetaField *g_igMatrixStack_dataMetaField;

igMetaObject *FUN_001e4740(void) {
    if (g_igMatrixStack_metaObject == 0) {
        g_igMatrixStack_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igMatrixStack_metaObject;
}

igMetaObject *igMatrixStack_GetMetaObject(void)
{
    igMetaObject *g = g_igMatrixStack_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001e4820();
    return g_igMatrixStack_metaObject;
}

int igMatrixStack_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igMatrixStack_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem) + 916));
}

void FUN_001e4820(void)
{
    igMetaObject_RunStaticInit(igMatrixStack_Register);
}

CallbackArray *igMatrixStack_Register(void) {
    DataPumpLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igMatrixStack_metaObject,
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igMatrixStack_GetMetaObject,
        "igMatrixStack",
        0x14, /* instance size */
        igMatrixStack_GetVTable,
        igMatrixStack_InitFields_001e48b0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igMatrixStack_GetMetaObject(void) {
    igMatrixStack_GetMetaObject();
}

void FUN_001e48b0(void) {
    int temp_s2;
    void **temp_v0;
    void *temp_s0;
    void *temp_s1;

    temp_s1 = (void *)(g_igMatrixStack_metaObject);
    temp_v0 = (void **)(igMetaObject_FindFieldByName((igMetaObject *)temp_s1, (const char *)("_data")));
    temp_s2 = ObjectPointerList_FindIndex((__internalNonRefCountedObjectList *)(*(int *)((char *)(temp_s1) + 40)), (int)temp_v0);
    temp_s0 = (void *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    *(int *)((char *)(temp_s0) + 60) = FUN_001888e0();
    *(int *)((char *)(temp_s0) + 56) = 0;
    *(int *)((char *)(temp_s0) + 28) = (int)(&g_igMatrixStack_dataMetaField);
    igMetaObject_FinalizeAndReplaceField((igMetaObject *)temp_s1, temp_s2, (igMetaField *)temp_s0);
    *(int *)((char *)(temp_s0) + 4) = (int)((int) (*(int *)((char *)(temp_s0) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_s0) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy((igObject *)temp_s0);
    }
}

