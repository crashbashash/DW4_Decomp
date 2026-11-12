void *FUN_003b20e0(void) {
    struct G *g = DAT_0058aa50[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003b21a0();
    }
    return DAT_0058aa50[0];
}

int beNDMWTitle2Info_GetVTable(void) {
    struct Obj_3b2130 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.w5 = 0;
    obj.w6 = 0;
    obj.vt = &DAT_0053dd50[0];
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_0053dd50[0];
    FUN_0033ec80(&obj, 0);
    return t;
}

void FUN_003b21a0(void)
{
    igMetaObject_RunStaticInit(beNDMWTitle2Info_Register);
}

void *beNDMWTitle2Info_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWTitle2Info_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beNDMWTitle2Info_GetMetaObject,
        beNDMWTitle2Info_className,
        0x1c, /* instance size */
        beNDMWTitle2Info_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWTitle2Info_GetMetaObject(void)
{
    FUN_003b20e0();
}

