void FUN_003ca380(int arg0) {
    FUN_003ca480();
    igMetaObject_CreateInstance(*(int *)0x58C108, arg0);
}

void *beNDMWGameRamInfo_ResolveMetaObject(void) {
    igMetaObject *g = g_beNDMWGameRamInfo_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003ca480();
    }
    return g_beNDMWGameRamInfo_metaObject[0];
}

int beNDMWGameRamInfo_GetVTable(void) {
    struct F_3ca410 f;
    int temp_s0;

    igObject_InitHeader(&f);
    f.w[1] = 0;
    f.w[4] = 0;
    f.w[5] = 0;
    f.vt = &DAT_0053c4e0[0];
    temp_s0 = *(int *)((char *)&f + *(int *)((char *)(g_objectSystem[0]) + 916));
    f.vt = &DAT_0053c4e0[0];
    FUN_0033ec80(&f, 0);
    return temp_s0;
}

void FUN_003ca480(void)
{
    igMetaObject_RunStaticInit(beNDMWGameRamInfo_Register);
}

void *beNDMWGameRamInfo_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWGameRamInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beNDMWGameRamInfo_GetMetaObject,
        beNDMWGameRamInfo_className,
        0x1c, /* instance size */
        beNDMWGameRamInfo_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWGameRamInfo_GetMetaObject(void)
{
    beNDMWGameRamInfo_ResolveMetaObject();
}

