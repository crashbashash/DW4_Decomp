void FUN_003b7520(int arg0) {
    FUN_003b7630();
    igMetaObject_CreateInstance(*(int *)0x58AD28, arg0);
}

igMetaObject *FUN_003b7560(void)
{
    igMetaObject *g = DAT_0058ad28[0];
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_003b7630();
    return DAT_0058ad28[0];
}

int beNDMWShopCtrlEditBit_GetVTable(void) {
    Obj_3b75b0 o;
    int r;

    igObject_InitHeader(&o);
    o.w[12] = 0;
    o.w[13] = 0;
    o.w[14] = 0;
    o.w[15] = 0;
    o.w[16] = 0;
    o.w[17] = 0;
    o.w[18] = 0;
    o.vt = &DAT_0053fa80[0];
    r = *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    o.vt = &DAT_0053fa80[0];
    beNDMWWindowCtrl_Destroy((beNDMWWindowCtrl *)&o, (long long)0);
    return r;
}

void FUN_003b7630(void)
{
    igMetaObject_RunStaticInit(beNDMWShopCtrlEditBit_Register);
}

void *beNDMWShopCtrlEditBit_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWShopCtrlEditBit_metaObject,
        beNDMWWindowCtrl_Register,
        beNDMWWindowCtrl_GetPublishedMetaObject,
        beNDMWShopCtrlEditBit_GetMetaObject,
        beNDMWShopCtrlEditBit_className,
        0x5c, /* instance size */
        beNDMWShopCtrlEditBit_GetVTable,
        beNDMWShopCtrlEditBit_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWShopCtrlEditBit_GetMetaObject(void)
{
    FUN_003b7560();
}

void beNDMWShopCtrlEditBit_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)((int *)DAT_0058ad28)[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c9a60[0], 2);
    igMetaObject_NameFields(temp_s0, &DAT_004c9a68[0], &DAT_004c9a70[0], &DAT_004c9a78[0], temp_s1);
}

