void *beNDMWLogoInfo_GetReadyMetaObject(void) {
    struct G *g = DAT_0058b528[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003c1f50();
    }
    return DAT_0058b528[0];
}

int beNDMWLogoInfo_GetVTable(void) {
    struct W_3c1ee0 o;
    int r;

    igObject_InitHeader(&o);
    o.f[1] = 0;
    o.f[4] = 0;
    o.f[5] = 0;
    o.vt = DAT_0053d370;
    r = *(int *)((char *)&o + *(int *)(((char * *)DAT_00586dc8)[0] + 916));
    o.vt = DAT_0053d370;
    FUN_0033ec80(&o, 0);
    return r;
}

void FUN_003c1f50(void)
{
    igMetaObject_RunStaticInit(beNDMWLogoInfo_Register);
}

void *beNDMWLogoInfo_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWLogoInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beNDMWLogoInfo_GetMetaObject,
        beNDMWLogoInfo_className,
        0x1c, /* instance size */
        beNDMWLogoInfo_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWLogoInfo_GetMetaObject(void)
{
    beNDMWLogoInfo_GetReadyMetaObject();
}

