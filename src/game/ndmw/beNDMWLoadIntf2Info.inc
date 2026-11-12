void *beNDMWLoadIntf2Info_GetReadyMetaObject(void) {
    struct G *g = DAT_0058b5d0[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003c2710();
    }
    return DAT_0058b5d0[0];
}

int beNDMWLoadIntf2Info_GetVTable(void) {
    union U_3c26a0 u;
    int t;

    igObject_InitHeader(u.b);
    *(int *)&u.b[8] = 0;
    *(int *)&u.b[20] = 0;
    *(int *)&u.b[24] = 0;
    u.vt = (int)&DAT_0053d2a0[0];
    t = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_0053d2a0[0];
    FUN_0033ec80(u.b, 0);
    return t;
}

void FUN_003c2710(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadIntf2Info_Register);
}

void *beNDMWLoadIntf2Info_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWLoadIntf2Info_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beNDMWLoadIntf2Info_GetMetaObject,
        beNDMWLoadIntf2Info_className,
        0x1c, /* instance size */
        beNDMWLoadIntf2Info_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWLoadIntf2Info_GetMetaObject(void)
{
    beNDMWLoadIntf2Info_GetReadyMetaObject();
}

