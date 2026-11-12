igMetaObject *FUN_0035cd40(void)
{
    igMetaObject *g = DAT_005892b0[0];
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_0035ce60();
    return DAT_005892b0[0];
}

int beLOA_GetVTable(void) {
    struct W_35cd90 o;
    int *p18;
    int *p17;
    int *p16;
    int r;

    igObject_InitHeader(&o);
    o.f[1] = 0;
    o.f[2] = 0;
    o.f[3] = 0;
    o.f[6] = 0;
    o.vt = &DAT_005364a0[0];
    p16 = &o.f[18];
    *p16 = 0;
    p17 = &o.f[19];
    *p17 = 0;
    p18 = &o.f[20];
    *p18 = 0;
    o.f[21] = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    o.vt = &DAT_005364a0[0];
    FUN_0019ab10(&o.f[21], -1);
    FUN_001ab380(p18, -1);
    FUN_001aaf00(p17, -1);
    FUN_0013bfe0(p16, -1);
    FUN_00195a90(&o, 0);
    return r;
}

void FUN_0035ce60(void)
{
    igMetaObject_RunStaticInit(beLOA_Register);
}

void *beLOA_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beLOA_metaObject,
        igGroup_Register,
        igGroup_GetPublishedMetaObject,
        beLOA_GetMetaObject,
        beLOA_className,
        0x60, /* instance size */
        beLOA_GetVTable,
        beLOA_InitFields,
        FUN_0035d050, /* extra callback item */
        g_beLOA_callbackList /* callback list */
    );
}

void beLOA_GetMetaObject(void)
{
    FUN_0035cd40();
}

void beLOA_InitFields(void) {
    int sp40[4];
    int temp_s0;
    void *temp_a0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s1;

    temp_s1 = (void *)((int *)DAT_005892b0)[0];
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_004c6470[0], 0xA);
    temp_a0 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 5));
    sp40[0] = 0x3F800000;
    sp40[1] = 0x3F800000;
    sp40[2] = 0x3F800000;
    sp40[3] = 0x3F800000;
    FUN_0018e670(temp_a0, sp40);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 6));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = FUN_0013af00();
    ((igRefMetaField *)temp_s2)->_construct = 1;
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 7));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = FUN_00139640();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 8));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = FUN_00139f10();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 9));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = FUN_00138f20();
    ((igRefMetaField *)temp_s2_4)->_construct = 1;
    igMetaObject_NameFields(temp_s1, &DAT_004c64a0[0], &DAT_004c64d0[0], &DAT_004c6500[0], temp_s0);
}

void FUN_0035d050(void)
{
    FUN_00389fb0();
}

