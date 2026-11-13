void beNDMWShopSelect03_Create(int arg0) {
    FUN_003b4a60();
    igMetaObject_CreateInstance(*(int *)0x58ABA8, arg0);
}

void *FUN_003b4990(void) {
    igMetaObject *g = g_beNDMWShopSelect03_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003b4a60();
    }
    return g_beNDMWShopSelect03_metaObject[0];
}

int beNDMWShopSelect03_GetVTable(void) {
    union U_3b49e0 u;
    int temp_s0;

    igObject_InitHeader(u.b);
    *(int *)&u.b[52] = 0;
    *(int *)&u.b[56] = 0;
    *(int *)&u.b[60] = 0;
    *(int *)&u.b[64] = 0;
    *(int *)&u.b[68] = 0;
    *(int *)&u.b[72] = 0;
    *(int *)&u.b[76] = 0;
    *(int *)&u.b[80] = 0;
    *(int *)&u.b[108] = 0;
    u.vt = (int)&DAT_00540140[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_00540140[0];
    FUN_003b4050((struct S_3b4050 *)u.b, (short)0);
    return temp_s0;
}

void FUN_003b4a60(void)
{
    igMetaObject_RunStaticInit(beNDMWShopSelect03_Register);
}

void *beNDMWShopSelect03_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWShopSelect03_metaObject,
        beNDMWWindowSelect_Register,
        beNDMWWindowSelect_GetPublishedMetaObject,
        beNDMWShopSelect03_GetMetaObject,
        beNDMWShopSelect03_className,
        0x70, /* instance size */
        beNDMWShopSelect03_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWShopSelect03_GetMetaObject(void)
{
    FUN_003b4990();
}

