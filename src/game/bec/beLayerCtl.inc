void FUN_0035caa0(int arg0) {
    FUN_0035cbf0();
    igMetaObject_CreateInstance(*(int *)0x589298, arg0);
}

int FUN_0035cae0(void) {
    if (((int *)DAT_00589298)[0] == 0) {
        ((int *)DAT_00589298)[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return ((int *)DAT_00589298)[0];
}

void *FUN_0035cb30(void) {
    struct G *g = DAT_00589298[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0035cbf0();
    }
    return DAT_00589298[0];
}

int beLayerCtl_GetVTable(void) {
    union U u;
    int temp_s0;
    int *p;

    igObject_InitHeader(u.b);
    *(int *)&u.b[8] = 0;
    *(int *)&u.b[24] = 0;
    u.vt = (int)&DAT_0053a940[0];
    p = (int *)&u.b[36];
    *p = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_0053a940[0];
    FUN_00343260((ObjectRefWord *)p, -1);
    FUN_0033f5e0((O_33f5e0 *)u.b, (short)0);
    return temp_s0;
}

void FUN_0035cbf0(void)
{
    igMetaObject_RunStaticInit(beLayerCtl_Register);
}

void *beLayerCtl_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beLayerCtl_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beLayerCtl_GetMetaObject,
        beLayerCtl_className,
        0x28, /* instance size */
        beLayerCtl_GetVTable,
        beLayerCtl_InitFields,
        0, /* extra callback item */
        g_beLayerCtl_callbackList /* callback list */
    );
}

void beLayerCtl_GetMetaObject(void)
{
    FUN_0035cb30();
}

void beLayerCtl_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)((int *)DAT_00589298)[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c6430[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00196930();
    igMetaObject_NameFields(temp_s0, &DAT_004c6438[0], &DAT_004c6440[0], &DAT_004c6448[0], temp_s2);
}

