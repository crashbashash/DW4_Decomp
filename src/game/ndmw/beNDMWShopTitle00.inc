void FUN_003b3370(int arg0) {
    FUN_003b3480();
    igMetaObject_CreateInstance(*(int *)0x58AB48, arg0);
}

void *FUN_003b33b0(void) {
    struct G *g = DAT_0058ab48[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003b3480();
    }
    return DAT_0058ab48[0];
}

int beNDMWShopTitle00_GetVTable(void) {
    union U_3b3400 u;
    int temp_s0;

    igObject_InitHeader(u.b);
    *(int *)&u.b[52] = 0;
    *(int *)&u.b[56] = 0;
    *(int *)&u.b[60] = 0;
    *(int *)&u.b[64] = 0;
    *(int *)&u.b[68] = 0;
    *(int *)&u.b[72] = 0;
    *(int *)&u.b[76] = 0;
    u.vt = (int)&DAT_005403e0[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_005403e0[0];
    FUN_003b3030((int **)u.b, (long long)0);
    return temp_s0;
}

void FUN_003b3480(void)
{
    igMetaObject_RunStaticInit(beNDMWShopTitle00_Register);
}

void *beNDMWShopTitle00_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWShopTitle00_metaObject,
        beNDMWWindowTitle_Register,
        beNDMWWindowTitle_GetPublishedMetaObject,
        beNDMWShopTitle00_GetMetaObject,
        beNDMWShopTitle00_className,
        0x50, /* instance size */
        beNDMWShopTitle00_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWShopTitle00_GetMetaObject(void)
{
    FUN_003b33b0();
}

