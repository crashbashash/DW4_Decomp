igMetaObject *g_beNDMWStageCtlInfo_metaObject;
igMetaEnum *g_beNDMWStageCtlInfo_messageMetaEnum;

igMetaObject *beNDMWStageCtlInfo_GetMetaObject(void)
{
    igMetaObject *g = g_beNDMWStageCtlInfo_metaObject;
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        beNDMWStageCtlInfo_EnsureRegistered();
    return g_beNDMWStageCtlInfo_metaObject;
}

int beNDMWStageCtlInfo_GetVTable(void) {
    union U_3bbc20 u;
    int temp_s0;

    igObject_InitHeader(u.b);
    *(int *)&u.b[8] = 0;
    *(int *)&u.b[20] = 0;
    *(int *)&u.b[24] = 0;
    u.vt = (int)&g_beNDMWStageCtlInfo_vtable[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_beNDMWStageCtlInfo_vtable[0];
    FUN_0033ec80(u.b, 0);
    return temp_s0;
}

void beNDMWStageCtlInfo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWStageCtlInfo_Register);
}

void *beNDMWStageCtlInfo_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWStageCtlInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beNDMWStageCtlInfo_GetMetaObjectFunction,
        "beNDMWStageCtlInfo",
        0x1c, /* instance size */
        beNDMWStageCtlInfo_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWStageCtlInfo_GetMetaObjectFunction(void)
{
    beNDMWStageCtlInfo_GetMetaObject();
}

static const char *g_beNDMWStageCtlInfo_messageNames[] = {
    "NEXTSTAGE",
    "PADINPUT",
    "ISRESETSTART",
};
static int g_beNDMWStageCtlInfo_messageValues[] = {
    0,
    1,
    2,
};

igMetaEnum *FUN_003bbd40(void) {
    if (g_beNDMWStageCtlInfo_messageMetaEnum == 0) {
        g_beNDMWStageCtlInfo_messageMetaEnum = igMetaEnum_Create("Message", g_beNDMWStageCtlInfo_messageNames, g_beNDMWStageCtlInfo_messageValues, 3);
    }
    return g_beNDMWStageCtlInfo_messageMetaEnum;
}

