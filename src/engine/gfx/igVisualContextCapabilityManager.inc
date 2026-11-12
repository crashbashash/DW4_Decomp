void FUN_00149bc0(void) {
    if (DAT_00554b1c == 0) {
        DAT_00554b1c = 1;
        FUN_0014bbb0();
        FUN_0014bd20();
        FUN_0014c670();
        FUN_0014d5c0();
        FUN_0014d6d0();
        FUN_0014f810();
        FUN_0014f920();
        FUN_0014ff00();
    }
}

void FUN_00149c30(int arg0) {
    FUN_00149d50();
    igMetaObject_CreateInstance(*(int *)0x55F8D0, arg0);
}

igMetaObject *igVisualContextCapabilityManager_GetMetaObject(void)
{
    igMetaObject *g = g_igVisualContextCapabilityManager_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00149d50();
    return g_igVisualContextCapabilityManager_metaObject[0];
}

int igVisualContextCapabilityManager_GetVTable(void) {
    Obj obj;
    int r;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00525de0[0];
    obj.ref = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_00525de0[0];
    obj.release();
    return r;
}

void FUN_00149d50(void)
{
    igMetaObject_RunStaticInit(igVisualContextCapabilityManager_Register);
}

void igVisualContextCapabilityManager_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igVisualContextCapabilityManager_metaObject,
        igCapabilityManager_Register,
        igCapabilityManager_GetPublishedMetaObject,
        thunk_igVisualContextCapabilityManager_GetMetaObject,
        igVisualContextCapabilityManager_className,
        0xC, /* instance size */
        igVisualContextCapabilityManager_GetVTable,
        &igVisualContextCapabilityManager_InitFields,
        0, /* extra callback item */
        g_igVisualContextCapabilityManager_callbackList /* callback list */
    );
}

void thunk_igVisualContextCapabilityManager_GetMetaObject(void) {
    igVisualContextCapabilityManager_GetMetaObject();
}

igMetaObject *FUN_00149df0(void) {
    return g_igCapabilityManager_metaObject[0];
}

void igVisualContextCapabilityManager_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igVisualContextCapabilityManager_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004882d8[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_0014a040();
    ((igMetaField *)temp_s1)->_persistent = 0;
    igMetaObject_NameFields(temp_s0, &DAT_004882e0[0], &DAT_004882e8[0], &DAT_004882f0[0], temp_s2);
}

