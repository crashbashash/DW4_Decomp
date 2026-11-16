igMetaObject *g_beHitLandDelivInfo_metaObject;

void *beHitLandDelivInfo_GetMetaObject(void) {
    igMetaObject *g = g_beHitLandDelivInfo_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beHitLandDelivInfo_EnsureRegistered();
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
    o.vt = &g_beHitLandDelivInfo_vtable[0];
    r = *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
    o.vt = &g_beHitLandDelivInfo_vtable[0];
    
    FUN_0033ec80((struct S_33ec80 *)&o, (short)0);
    return r;
}

void beHitLandDelivInfo_EnsureRegistered(void)
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
        beHitLandDelivInfo_GetMetaObjectFunction,
        "beHitLandDelivInfo",
        0x1c, /* instance size */
        beHitLandDelivInfo_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beHitLandDelivInfo_GetMetaObjectFunction(void)
{
    beHitLandDelivInfo_GetMetaObject();
}

igMetaEnum *g_beHitLandDelivInfo_messageMetaEnum;
static const char *g_beHitLandDelivInfo_messageNames[] = {
    "HITWALL", "HITWALLFULL", "HITFLOORCHECK", "HITFLOORADJUST",
    "HITFLOOR",
};
static int g_beHitLandDelivInfo_messageValues[] = {
    0, 1, 2, 3, 4,
};

igMetaEnum *beHitLandDelivInfo_GetMessageEnum(void) {
    if (g_beHitLandDelivInfo_messageMetaEnum == 0) {
        g_beHitLandDelivInfo_messageMetaEnum = igMetaEnum_Create("Message", g_beHitLandDelivInfo_messageNames, g_beHitLandDelivInfo_messageValues, 5);
    }
    return g_beHitLandDelivInfo_messageMetaEnum;
}

