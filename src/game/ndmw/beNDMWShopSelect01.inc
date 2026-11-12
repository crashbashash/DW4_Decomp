void FUN_003b4d90(int arg0) {
    FUN_003b4ea0();
    igMetaObject_CreateInstance(*(int *)0x58ABC0, arg0);
}

void *FUN_003b4dd0(void) {
    igMetaObject *g = g_beNDMWShopSelect01_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003b4ea0();
    }
    return g_beNDMWShopSelect01_metaObject[0];
}

int beNDMWShopSelect01_GetVTable(void) {
    union U_3b4e20 u;
    int temp_s0;

    igObject_InitHeader(u.b);
    u.w[13] = 0;
    u.w[14] = 0;
    u.w[15] = 0;
    u.w[16] = 0;
    u.w[17] = 0;
    u.w[18] = 0;
    u.w[19] = 0;
    u.w[20] = 0;
    u.w[27] = 0;
    u.w[0] = (int)(&DAT_00540220[0]);
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.w[0] = (int)(&DAT_00540220[0]);
    FUN_003b4050((struct S_3b4050 *)(&u.w[0]), (short)0);
    return temp_s0;
}

void FUN_003b4ea0(void)
{
    igMetaObject_RunStaticInit(beNDMWShopSelect01_Register);
}

void *beNDMWShopSelect01_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWShopSelect01_metaObject,
        beNDMWWindowSelect_Register,
        beNDMWWindowSelect_GetPublishedMetaObject,
        beNDMWShopSelect01_GetMetaObject,
        beNDMWShopSelect01_className,
        0x70, /* instance size */
        beNDMWShopSelect01_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWShopSelect01_GetMetaObject(void)
{
    FUN_003b4dd0();
}

