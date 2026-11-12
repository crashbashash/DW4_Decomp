void FUN_003bb790(int arg0) {
    FUN_003bb8e0();
    igMetaObject_CreateInstance(*(int *)0x58B028, arg0);
}

int FUN_003bb7d0(void) {
    if (((int *)DAT_0058b028)[0] == 0) {
        ((int *)DAT_0058b028)[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return ((int *)DAT_0058b028)[0];
}

void *FUN_003bb820(void) {
    struct G *g = DAT_0058b028[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003bb8e0();
    }
    return DAT_0058b028[0];
}

int beNDMWStatus_GetVTable(void) {
    union U_3bb870 u;
    int t;
    char *ps;

    igObject_InitHeader(u.b);
    *(int *)&u.b[8] = 0;
    *(int *)&u.b[24] = 0;
    u.vt = (int)&DAT_0053e7c0[0];
    ps = &u.b[32];
    *(int *)ps = 0;
    t = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_0053e7c0[0];
    FUN_003b2f30((void **)ps, -1);
    FUN_0033f5e0(u.b, 0);
    return t;
}

void FUN_003bb8e0(void)
{
    igMetaObject_RunStaticInit(beNDMWStatus_Register);
}

void *beNDMWStatus_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWStatus_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beNDMWStatus_GetMetaObject,
        beNDMWStatus_className,
        0x2c, /* instance size */
        beNDMWStatus_GetVTable,
        beNDMWStatus_InitFields,
        0, /* extra callback item */
        g_beNDMWStatus_callbackList /* callback list */
    );
}

void beNDMWStatus_GetMetaObject(void)
{
    FUN_003bb820();
}

void beNDMWStatus_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)((int *)DAT_0058b028)[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004ca0d8[0], 3);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_003b1dd0();
    igMetaObject_NameFields(temp_s0, &DAT_004ca0e8[0], &DAT_004ca0f8[0], &DAT_004ca108[0], temp_s2);
}

