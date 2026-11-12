igMetaObject *FUN_003bbbd0(void)
{
    igMetaObject *g = DAT_0058b050[0];
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_003bbc90();
    return DAT_0058b050[0];
}

int beNDMWStageCtlInfo_GetVTable(void) {
    union U_3bbc20 u;
    int temp_s0;

    igObject_InitHeader(u.b);
    *(int *)&u.b[8] = 0;
    *(int *)&u.b[20] = 0;
    *(int *)&u.b[24] = 0;
    u.vt = (int)&DAT_0053d9d0[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_0053d9d0[0];
    FUN_0033ec80(u.b, 0);
    return temp_s0;
}

void FUN_003bbc90(void)
{
    igMetaObject_RunStaticInit(beNDMWStageCtlInfo_Register);
}

void *beNDMWStageCtlInfo_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWStageCtlInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beNDMWStageCtlInfo_GetMetaObject,
        beNDMWStageCtlInfo_className,
        0x1c, /* instance size */
        beNDMWStageCtlInfo_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWStageCtlInfo_GetMetaObject(void)
{
    FUN_003bbbd0();
}

int FUN_003bbd40(void) {
    if (DAT_0058b058[0] == 0) {
        DAT_0058b058[0] = igMetaEnum_Create(&DAT_00510d58[0], &DAT_004ca118[0], &DAT_004ca128[0], 3);
    }
    return DAT_0058b058[0];
}

