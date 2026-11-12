void *beNDMWPanelWazaInfo_ResolveMetaObject(void) {
    struct G *g = DAT_0058b1e8[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003bd750();
    }
    return DAT_0058b1e8[0];
}

int beNDMWPanelWazaInfo_GetVTable(void) {
    struct Obj_3bd6e0 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.w5 = 0;
    obj.w6 = 0;
    obj.vt = &DAT_0053d690[0];
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_0053d690[0];
    FUN_0033ec80(&obj, 0);
    return t;
}

void FUN_003bd750(void)
{
    igMetaObject_RunStaticInit(beNDMWPanelWazaInfo_Register);
}

void *beNDMWPanelWazaInfo_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWPanelWazaInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beNDMWPanelWazaInfo_GetMetaObject,
        beNDMWPanelWazaInfo_className,
        0x1c, /* instance size */
        beNDMWPanelWazaInfo_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWPanelWazaInfo_GetMetaObject(void)
{
    beNDMWPanelWazaInfo_ResolveMetaObject();
}

