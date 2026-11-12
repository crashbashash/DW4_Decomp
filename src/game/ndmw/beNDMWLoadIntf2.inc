void FUN_003c4700(int arg0) {
    FUN_003c4850();
    igMetaObject_CreateInstance(*(int *)0x58BAC8, arg0);
}

int FUN_003c4740(void) {
    if (((int *)DAT_0058bac8)[0] == 0) {
        ((int *)DAT_0058bac8)[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return ((int *)DAT_0058bac8)[0];
}

void *beNDMWLoadIntf2_ResolveMetaObject(void) {
    struct G *g = DAT_0058bac8[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003c4850();
    }
    return DAT_0058bac8[0];
}

int beNDMWLoadIntf2_GetVTable(void) {
    struct Obj_3c47e0 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.w[1] = 0;
    obj.w[5] = 0;
    obj.vt = &DAT_0053e860[0];
    obj.w[8] = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_0053e860[0];
    FUN_0033dda0(&obj.w[8], -1);
    FUN_0033f5e0(&obj, 0);
    return r;
}

void FUN_003c4850(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadIntf2_Register);
}

void *beNDMWLoadIntf2_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWLoadIntf2_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beNDMWLoadIntf2_GetMetaObject,
        beNDMWLoadIntf2_className,
        0x30, /* instance size */
        beNDMWLoadIntf2_GetVTable,
        beNDMWLoadIntf2_InitFields,
        0, /* extra callback item */
        g_beNDMWLoadIntf2_callbackList /* callback list */
    );
}

void beNDMWLoadIntf2_GetMetaObject(void)
{
    beNDMWLoadIntf2_ResolveMetaObject();
}

void beNDMWLoadIntf2_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)((int *)DAT_0058bac8)[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004cb760[0], 4);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0034c8e0();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_00342ce0();
    ((igObjectRefMetaField *)temp_s1_2)->_refCounted = 0;
    igMetaObject_NameFields(temp_s0, &DAT_004cb770[0], &DAT_004cb780[0], &DAT_004cb790[0], temp_s2);
}

