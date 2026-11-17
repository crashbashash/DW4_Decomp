igMetaObject *g_igCharMetricsList_metaObject;
int g_igCharMetricsList_externalStorage;

igMetaObject *FUN_00452790(void) {
    if (g_igCharMetricsList_metaObject == 0) {
        g_igCharMetricsList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igCharMetricsList_metaObject;
}

igMetaObject *igCharMetricsList_GetMetaObject(void)
{
    igMetaObject *g = g_igCharMetricsList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igCharMetricsList_RunStaticInit();
    return g_igCharMetricsList_metaObject;
}

int igCharMetricsList_GetVTable(void) {
    Obj_452830 o;

    igObject_InitHeader((igObject *)&o);
    o.vt = &g_igCharMetricsList_vtable[0];
    return *(int *)((char *)&o + *(int *)((char *)(g_objectSystem) + 916));
}

void igCharMetricsList_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igCharMetricsList_Register);
}

CallbackArray *igCharMetricsList_Register(void) {
    GuiLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igCharMetricsList_metaObject,
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igCharMetricsList_GetMetaObject,
        "igCharMetricsList",
        0x14, /* instance size */
        igCharMetricsList_GetVTable,
        FUN_00452900,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igCharMetricsList_GetMetaObject(void) {
    igCharMetricsList_GetMetaObject();
}

void FUN_00452900(void) {
    int temp_s2;
    void **temp_v0;
    void *temp_s0;
    void *temp_s1;

    temp_s1 = (void *)(g_igCharMetricsList_metaObject);
    temp_v0 = (void **)(igMetaObject_FindFieldByName((igMetaObject *)temp_s1, "_data"));
    temp_s2 = ObjectPointerList_FindIndex((__internalNonRefCountedObjectList *)(*(int *)((char *)(temp_s1) + 40)), (int)temp_v0);
    temp_s0 = (void *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    *(int *)((char *)(temp_s0) + 60) = FUN_00452c40();
    *(int *)((char *)(temp_s0) + 56) = 0;
    *(int *)((char *)(temp_s0) + 28) = (int)(&g_igCharMetricsList_externalStorage);
    igMetaObject_FinalizeAndReplaceField((igMetaObject *)temp_s1, temp_s2, (igMetaField *)temp_s0);
    *(int *)((char *)(temp_s0) + 4) = (int)((int) (*(int *)((char *)(temp_s0) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_s0) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy((igObject *)temp_s0);
    }
}

