igMetaObject *g_beHitLandDelivInfo_metaObject;

void *FUN_0035e9c0(void) {
    igMetaObject *g = g_beHitLandDelivInfo_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_0035ea80();
    }
    return g_beHitLandDelivInfo_metaObject;
}

int beHitLandDelivInfo_GetVTable(void) {
    struct Obj_35ea10 o;
    int r;
    igObject_InitHeader(&o);
    o.f8 = 0;
    o.f20 = 0;
    o.f24 = 0;
    o.vt = &DAT_005361c0[0];
    r = *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
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
        &g_beHitLandDelivInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beHitLandDelivInfo_GetMetaObject,
        "beHitLandDelivInfo",
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

igMetaEnum *g_beHitLandDelivInfo_messageMetaEnum;
static const char *g_beHitLandDelivInfo_messageNames[] = {
    "HITWALL", "HITWALLFULL", "HITFLOORCHECK", "HITFLOORADJUST",
    "HITFLOOR",
};
static int g_beHitLandDelivInfo_messageValues[] = {
    0, 1, 2, 3, 4,
};

igMetaEnum *FUN_0035eb30(void) {
    if (g_beHitLandDelivInfo_messageMetaEnum == 0) {
        g_beHitLandDelivInfo_messageMetaEnum = igMetaEnum_Create("Message", g_beHitLandDelivInfo_messageNames, g_beHitLandDelivInfo_messageValues, 5);
    }
    return g_beHitLandDelivInfo_messageMetaEnum;
}

