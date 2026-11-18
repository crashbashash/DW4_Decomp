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
    beNDMWStageCtlInfo obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._dataList = 0;
    obj._ramList = 0;
    *(int **)&obj._vtable = &g_beNDMWStageCtlInfo_vtable[0];
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    *(int **)&obj._vtable = &g_beNDMWStageCtlInfo_vtable[0];
    beBaseInfo_Destroy((beBaseInfo *)&obj, 0);
    return vtable;
}

void beNDMWStageCtlInfo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWStageCtlInfo_Register);
}

CallbackArray *beNDMWStageCtlInfo_Register(void) {
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

igMetaEnum *beNDMWStageCtlInfo_GetMessageEnum(void) {
    if (g_beNDMWStageCtlInfo_messageMetaEnum == 0) {
        g_beNDMWStageCtlInfo_messageMetaEnum = igMetaEnum_Create("Message", g_beNDMWStageCtlInfo_messageNames, g_beNDMWStageCtlInfo_messageValues, 3);
    }
    return g_beNDMWStageCtlInfo_messageMetaEnum;
}

