igMetaObject *FUN_00452790(void) {
    if (g_igCharMetricsList_metaObject[0] == 0) {
        g_igCharMetricsList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igCharMetricsList_metaObject[0];
}

igMetaObject *igCharMetricsList_GetMetaObject(void)
{
    igMetaObject *g = g_igCharMetricsList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igCharMetricsList_RunStaticInit();
    return g_igCharMetricsList_metaObject[0];
}

int igCharMetricsList_GetVTable(void) {
    Obj_452830 o;

    igObject_InitHeader(&o);
    o.vt = &DAT_00541780[0];
    return *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void igCharMetricsList_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igCharMetricsList_Register);
}

void igCharMetricsList_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igCharMetricsList_metaObject,
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igCharMetricsList_GetMetaObject,
        igCharMetricsList_className,
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

    temp_s1 = (void *)(g_igCharMetricsList_metaObject[0]);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, &DAT_0051e798[0]));
    temp_s2 = ObjectPointerList_FindIndex(*(int *)((char *)(temp_s1) + 40), temp_v0);
    temp_s0 = (void *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    *(int *)((char *)(temp_s0) + 60) = FUN_00452c40();
    *(int *)((char *)(temp_s0) + 56) = 0;
    *(int *)((char *)(temp_s0) + 28) = (int)(&DAT_0058c640[0]);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s2, temp_s0);
    *(int *)((char *)(temp_s0) + 4) = (int)((int) (*(int *)((char *)(temp_s0) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_s0) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_s0);
    }
}

