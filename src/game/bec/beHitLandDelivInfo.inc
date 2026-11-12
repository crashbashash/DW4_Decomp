void *FUN_0035e9c0(void) {
    struct G *g = DAT_00589450[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0035ea80();
    }
    return DAT_00589450[0];
}

int beHitLandDelivInfo_GetVTable(void) {
    struct Obj_35ea10 o;
    int r;
    igObject_InitHeader(&o);
    o.f8 = 0;
    o.f20 = 0;
    o.f24 = 0;
    o.vt = &DAT_005361c0[0];
    r = *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    o.vt = &DAT_005361c0[0];
    
    FUN_0033ec80((struct S_33ec80 *)&o, (short)0);
    return r;
}

void FUN_0035ea80(void)
{
    igMetaObject_RunStaticInit(beHitLandDelivInfo_Register);
}

void *beHitLandDelivInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beHitLandDelivInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beHitLandDelivInfo_GetMetaObject,
        beHitLandDelivInfo_className,
        0x1c, /* instance size */
        beHitLandDelivInfo_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beHitLandDelivInfo_GetMetaObject(void)
{
    FUN_0035e9c0();
}

int FUN_0035eb30(void) {
    if (DAT_00589458[0] == 0) {
        DAT_00589458[0] = igMetaEnum_Create(&DAT_00501a58[0], &DAT_004c6850[0], &DAT_004c6870[0], 5);
    }
    return DAT_00589458[0];
}

