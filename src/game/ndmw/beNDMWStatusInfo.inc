void *FUN_003b5a40(void) {
    struct G *g = DAT_0058ac30[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003b5b00();
    }
    return DAT_0058ac30[0];
}

int beNDMWStatusInfo_GetVTable(void) {
    struct Obj_3b5a90 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.w[1] = 0;
    obj.w[4] = 0;
    obj.w[5] = 0;
    obj.vt = &DAT_0053dbc0[0];
    r = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_0053dbc0[0];
    FUN_0033ec80(&obj, 0);
    return r;
}

void FUN_003b5b00(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusInfo_Register);
}

void *beNDMWStatusInfo_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWStatusInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beNDMWStatusInfo_GetMetaObject,
        beNDMWStatusInfo_className,
        0x1c, /* instance size */
        beNDMWStatusInfo_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWStatusInfo_GetMetaObject(void)
{
    FUN_003b5a40();
}

