void FUN_003c7da0(int arg0) {
    FUN_003c7ef0();
    igMetaObject_CreateInstance(*(int *)0x58BEF0, arg0);
}

int FUN_003c7de0(void) {
    if (((int *)DAT_0058bef0)[0] == 0) {
        ((int *)DAT_0058bef0)[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return ((int *)DAT_0058bef0)[0];
}

igMetaObject *beNDMWLoadCtrl2_GetReadyMetaObject(void)
{
    igMetaObject *g = DAT_0058bef0[0];
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_003c7ef0();
    return DAT_0058bef0[0];
}

int beNDMWLoadCtrl2_GetVTable(void) {
    struct Obj_3c7e80 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.w[1] = 0;
    obj.w[5] = 0;
    obj.vt = &DAT_0053e900[0];
    obj.w[7] = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_0053e900[0];
    FUN_0033dda0(&obj.w[7], -1);
    FUN_0033f5e0(&obj, 0);
    return r;
}

void FUN_003c7ef0(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadCtrl2_Register);
}

void *beNDMWLoadCtrl2_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWLoadCtrl2_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beNDMWLoadCtrl2_GetMetaObject,
        beNDMWLoadCtrl2_className,
        0x2c, /* instance size */
        beNDMWLoadCtrl2_GetVTable,
        beNDMWLoadCtrl2_InitFields,
        0, /* extra callback item */
        g_beNDMWLoadCtrl2_callbackList /* callback list */
    );
}

void beNDMWLoadCtrl2_GetMetaObject(void)
{
    beNDMWLoadCtrl2_GetReadyMetaObject();
}

void beNDMWLoadCtrl2_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)((int *)DAT_0058bef0)[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004cc048[0], 3);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0034c8e0();
    igMetaObject_NameFields(temp_s0, &DAT_004cc058[0], &DAT_004cc068[0], &DAT_004cc078[0], temp_s2);
}

