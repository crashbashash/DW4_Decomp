void FUN_001e5650(int arg0) {
    FUN_001e5810();
    igMetaObject_CreateInstance(*(int *)0x562C10, arg0);
}

int FUN_001e5690(void) {
    if (DAT_00562c10[0] == 0) {
        DAT_00562c10[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_00562c10[0];
}

igMetaObject *igDataPumpInfo_GetMetaObject(void)
{
    igMetaObject *g = g_igDataPumpInfo_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001e5810();
    return g_igDataPumpInfo_metaObject[0];
}

int igDataPumpInfo_GetVTable(void) {
    Obj_1e5730 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.r1 = 0;
    obj.vt = &DAT_0052ba10[0];
    obj.r4 = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_0052ba10[0];
    obj.rel4();
    obj.vt = &DAT_00524950[0];
    obj.rel1();
    return r;
}

void FUN_001e5810(void)
{
    igMetaObject_RunStaticInit(igDataPumpInfo_Register);
}

void igDataPumpInfo_Register(void) {
    DataPumpLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igDataPumpInfo_metaObject,
        igInfo_Register,
        igInfo_GetPublishedMetaObject,
        thunk_igDataPumpInfo_GetMetaObject,
        igDataPumpInfo_className,
        0x18, /* instance size */
        igDataPumpInfo_GetVTable,
        &igDataPumpInfo_InitFields,
        0, /* extra callback item */
        g_igDataPumpInfo_callbackList /* callback list */
    );
}

void thunk_igDataPumpInfo_GetMetaObject(void) {
    igDataPumpInfo_GetMetaObject();
}

void igDataPumpInfo_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_00562c10[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048dbb8[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_001e53c0();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_0048dbc0[0], &DAT_0048dbc8[0], &DAT_0048dbd0[0], temp_s2);
}

