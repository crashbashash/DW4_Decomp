void *FUN_0034c380(void) {
    igMetaObject *g = g_beParticleCtrl2Info_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_0034c460();
    }
    return g_beParticleCtrl2Info_metaObject[0];
}

int beParticleCtrl2Info_GetVTable(void) {
    struct Obj_34c3d0 o;
    int r;

    igObject_InitHeader(&o);
    o.f8 = 0;
    o.f14 = 0;
    o.f18 = 0;
    o.vt = &DAT_00538670[0];
    o.f1c = 0;
    o.f20 = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
    o.vt = &DAT_00538670[0];
    FUN_00343260((ObjectRefWord *)&o.f20, -1);
    FUN_00343260((ObjectRefWord *)&o.f1c, -1);
    FUN_0033ec80((struct S_33ec80 *)&o, (short)0);
    return r;
}

void FUN_0034c460(void)
{
    igMetaObject_RunStaticInit(beParticleCtrl2Info_Register);
}

void *beParticleCtrl2Info_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beParticleCtrl2Info_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beParticleCtrl2Info_GetMetaObject,
        beParticleCtrl2Info_className,
        0x30, /* instance size */
        beParticleCtrl2Info_GetVTable,
        beParticleCtrl2Info_InitFields,
        0, /* extra callback item */
        g_beParticleCtrl2Info_callbackList /* callback list */
    );
}

void beParticleCtrl2Info_GetMetaObject(void)
{
    FUN_0034c380();
}

void beParticleCtrl2Info_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beParticleCtrl2Info_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c4630[0], 4);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00196930();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_00196930();
    igMetaObject_NameFields(temp_s0, &DAT_004c4640[0], &DAT_004c4650[0], &DAT_004c4660[0], temp_s2);
}

int FUN_0034c5d0(void) {
    if (DAT_00588508[0] == 0) {
        DAT_00588508[0] = igMetaEnum_Create(&DAT_00501a58[0], &DAT_004c4670[0], &DAT_004c4690[0], 8);
    }
    return DAT_00588508[0];
}

