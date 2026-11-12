void FUN_003b8630(int arg0) {
    FUN_003b8740();
    igMetaObject_CreateInstance(*(int *)0x58ADF8, arg0);
}

void *FUN_003b8670(void) {
    struct G *g = DAT_0058adf8[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003b8740();
    }
    return DAT_0058adf8[0];
}

int beNDMWShopCtrl30_GetVTable(void) {
    struct F_3b86c0 f;
    int temp_s0;

    igObject_InitHeader(&f);
    f.w[12] = 0;
    f.w[13] = 0;
    f.w[14] = 0;
    f.w[15] = 0;
    f.w[16] = 0;
    f.w[17] = 0;
    f.w[18] = 0;
    f.vt = &DAT_0053fdf0[0];
    temp_s0 = *(int *)((char *)&f + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    f.vt = &DAT_0053fdf0[0];
    FUN_003b6430(&f, 0);
    return temp_s0;
}

void FUN_003b8740(void)
{
    igMetaObject_RunStaticInit(beNDMWShopCtrl30_Register);
}

void *beNDMWShopCtrl30_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWShopCtrl30_metaObject,
        beNDMWWindowCtrl_Register,
        beNDMWWindowCtrl_GetPublishedMetaObject,
        beNDMWShopCtrl30_GetMetaObject,
        beNDMWShopCtrl30_className,
        0x58, /* instance size */
        beNDMWShopCtrl30_GetVTable,
        beNDMWShopCtrl30_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWShopCtrl30_GetMetaObject(void)
{
    FUN_003b8670();
}

void beNDMWShopCtrl30_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)((int *)DAT_0058adf8)[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c9c08[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_004c9c10[0], &DAT_004c9c18[0], &DAT_004c9c20[0], temp_s1);
}

