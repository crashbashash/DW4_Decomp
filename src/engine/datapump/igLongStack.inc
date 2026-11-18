igMetaObject *g_igLongStack_metaObject;
igMetaField *g_igLongStack_dataMetaField;

igMetaObject *FUN_001e4010(void) {
    if (g_igLongStack_metaObject == 0) {
        g_igLongStack_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igLongStack_metaObject;
}

igMetaObject *igLongStack_GetMetaObject(void)
{
    igMetaObject *g = g_igLongStack_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001e40f0();
    return g_igLongStack_metaObject;
}

int igLongStack_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igLongStack_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void FUN_001e40f0(void)
{
    igMetaObject_RunStaticInit(igLongStack_Register);
}

CallbackArray *igLongStack_Register(void) {
    DataPumpLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igLongStack_metaObject,
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igLongStack_GetMetaObject,
        "igLongStack",
        0x14, /* instance size */
        igLongStack_GetVTable,
        igLongStack_InitFields_001e4180,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igLongStack_GetMetaObject(void) {
    igLongStack_GetMetaObject();
}

void FUN_001e4180(void) {
    int temp_s2;
    void **temp_v0;
    void *temp_s0;
    void *temp_s1;

    temp_s1 = (void *)(g_igLongStack_metaObject);
    temp_v0 = (void **)(igMetaObject_FindFieldByName((igMetaObject *)temp_s1, (const char *)("_data")));
    temp_s2 = ObjectPointerList_FindIndex((__internalNonRefCountedObjectList *)(*(int *)((char *)(temp_s1) + 40)), (int)temp_v0);
    temp_s0 = (void *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    *(int *)((char *)(temp_s0) + 60) = igLongMetaField_GetDefaultDescriptor();
    *(int *)((char *)(temp_s0) + 56) = 0;
    *(int *)((char *)(temp_s0) + 28) = (int)(&g_igLongStack_dataMetaField);
    igMetaObject_FinalizeAndReplaceField((igMetaObject *)temp_s1, temp_s2, (igMetaField *)temp_s0);
    *(int *)((char *)(temp_s0) + 4) = (int)((int) (*(int *)((char *)(temp_s0) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_s0) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy((igObject *)temp_s0);
    }
}

