void FUN_003c2340(int arg0) {
    FUN_003c2490();
    igMetaObject_CreateInstance(*(int *)0x58B570, arg0);
}

int FUN_003c2380(void) {
    if (((int *)DAT_0058b570)[0] == 0) {
        ((int *)DAT_0058b570)[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return ((int *)DAT_0058b570)[0];
}

void *beNDMWLogo_GetReadyMetaObject(void) {
    struct G *g = DAT_0058b570[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003c2490();
    }
    return DAT_0058b570[0];
}

int beNDMWLogo_GetVTable(void) {
    struct Obj_3c2420 obj;
    int temp_s0;

    igObject_InitHeader(&obj);
    obj.f8 = 0;
    obj.f18 = 0;
    obj.vt = (&DAT_005409d0[0]);
    obj.f28 = 0;
    temp_s0 = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = (&DAT_005409d0[0]);
    FUN_003b2a10((ObjectRefWord *)&obj.f28, -1);
    FUN_0033f5e0(&obj, 0);
    return temp_s0;
}

void FUN_003c2490(void)
{
    igMetaObject_RunStaticInit(beNDMWLogo_Register);
}

void *beNDMWLogo_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWLogo_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beNDMWLogo_GetMetaObject,
        beNDMWLogo_className,
        0x5c, /* instance size */
        beNDMWLogo_GetVTable,
        beNDMWLogo_InitFields,
        0, /* extra callback item */
        g_beNDMWLogo_callbackList /* callback list */
    );
}

void beNDMWLogo_GetMetaObject(void)
{
    beNDMWLogo_GetReadyMetaObject();
}

void beNDMWLogo_InitFields(void) {
    int temp_s2;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)((int *)DAT_0058b570)[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004cac60[0], 0xB);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0034c8e0();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_00342ce0();
    ((igObjectRefMetaField *)temp_s1_2)->_refCounted = 0;
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = FUN_003c5200();
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 6), 1);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 9), -1);
    igMetaObject_NameFields(temp_s0, &DAT_004cac90[0], &DAT_004cacc0[0], &DAT_004cacf0[0], temp_s2);
}

