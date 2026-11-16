igMetaObject *g_beNDMWShopCtrlSell_metaObject;

void beNDMWShopCtrlSell_Create(int arg0) {
    beNDMWShopCtrlSell_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWShopCtrlSell_metaObject, arg0);
}

void *beNDMWShopCtrlSell_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWShopCtrlSell_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWShopCtrlSell_EnsureRegistered();
    }
    return g_beNDMWShopCtrlSell_metaObject;
}

int beNDMWShopCtrlSell_GetVTable(void) {
    union U_3b73f0 u;
    int temp_s0;

    igObject_InitHeader(u.b);
    u.w[13] = 0;
    u.w[14] = 0;
    u.w[15] = 0;
    u.w[16] = 0;
    u.w[17] = 0;
    u.w[18] = 0;
    u.w[19] = 0;
    u.w[0] = (int)(&g_beNDMWShopCtrlSell_vtable[0]);
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.w[0] = (int)(&g_beNDMWShopCtrlSell_vtable[0]);
    beNDMWWindowCtrl_Destroy((beNDMWWindowCtrl *)(&u.w[0]), (long long)0);
    return temp_s0;
}

void beNDMWShopCtrlSell_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWShopCtrlSell_Register);
}

void *beNDMWShopCtrlSell_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWShopCtrlSell_metaObject,
        beNDMWWindowCtrl_Register,
        beNDMWWindowCtrl_GetPublishedMetaObject,
        beNDMWShopCtrlSell_GetMetaObjectFunction,
        "beNDMWShopCtrlSell",
        0x54, /* instance size */
        beNDMWShopCtrlSell_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWShopCtrlSell_GetMetaObjectFunction(void)
{
    beNDMWShopCtrlSell_GetMetaObject();
}

