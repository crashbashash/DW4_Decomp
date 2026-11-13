void beNDMWSaveCtrl_CreateInstance(int arg0) {
    FUN_003bd540();
    igMetaObject_CreateInstance(*(int *)0x58B1D8, arg0);
}

igMetaObject *FUN_003bd430(void) {
    if (g_beNDMWSaveCtrl_metaObject[0] == 0) {
        g_beNDMWSaveCtrl_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_beNDMWSaveCtrl_metaObject[0];
}

void *beNDMWSaveCtrl_ResolveMetaObject(void) {
    igMetaObject *g = g_beNDMWSaveCtrl_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003bd540();
    }
    return g_beNDMWSaveCtrl_metaObject[0];
}

int beNDMWSaveCtrl_GetVTable(void) {
    union U_3bd4d0 u;
    int temp_s0;
    char *ps;

    igObject_InitHeader(u.b);
    *(int *)&u.b[8] = 0;
    *(int *)&u.b[24] = 0;
    u.vt = (int)&DAT_0053eae0[0];
    ps = &u.b[32];
    *(int *)ps = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_0053eae0[0];
    FUN_0033dda0(ps, -1);
    FUN_0033f5e0(u.b, 0);
    return temp_s0;
}

void FUN_003bd540(void)
{
    igMetaObject_RunStaticInit(beNDMWSaveCtrl_Register);
}

void *beNDMWSaveCtrl_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWSaveCtrl_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beNDMWSaveCtrl_GetMetaObject,
        beNDMWSaveCtrl_className,
        0x24, /* instance size */
        beNDMWSaveCtrl_GetVTable,
        beNDMWSaveCtrl_InitFields,
        0, /* extra callback item */
        g_beNDMWSaveCtrl_callbackList /* callback list */
    );
}

void beNDMWSaveCtrl_GetMetaObject(void)
{
    beNDMWSaveCtrl_ResolveMetaObject();
}

void beNDMWSaveCtrl_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beNDMWSaveCtrl_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004ca438[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0034c8e0();
    igMetaObject_NameFields(temp_s0, &DAT_004ca440[0], &DAT_004ca448[0], &DAT_004ca450[0], temp_s2);
}

