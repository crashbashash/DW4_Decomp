void beNDMWShopCtrl10_Create(int arg0) {
    FUN_003b8c70();
    igMetaObject_CreateInstance(*(int *)0x58AE18, arg0);
}

void *FUN_003b8ba0(void) {
    igMetaObject *g = g_beNDMWShopCtrl10_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003b8c70();
    }
    return g_beNDMWShopCtrl10_metaObject[0];
}

int beNDMWShopCtrl10_GetVTable(void) {
    struct W_3b8bf0 o;
    int r;

    igObject_InitHeader(&o);
    o.w[12] = 0;
    o.w[13] = 0;
    o.w[14] = 0;
    o.w[15] = 0;
    o.w[16] = 0;
    o.w[17] = 0;
    o.w[18] = 0;
    o.vt = DAT_0053fe50;
    r = *(int *)((char *)&o + *(int *)(((char * *)g_objectSystem)[0] + 916));
    o.vt = DAT_0053fe50;
    beNDMWWindowCtrl_Destroy((beNDMWWindowCtrl *)&o, (long long)0);
    return r;
}

void FUN_003b8c70(void)
{
    igMetaObject_RunStaticInit(beNDMWShopCtrl10_Register);
}

void *beNDMWShopCtrl10_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWShopCtrl10_metaObject,
        beNDMWWindowCtrl_Register,
        beNDMWWindowCtrl_GetPublishedMetaObject,
        beNDMWShopCtrl10_GetMetaObject,
        beNDMWShopCtrl10_className,
        0x5c, /* instance size */
        beNDMWShopCtrl10_GetVTable,
        beNDMWShopCtrl10_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWShopCtrl10_GetMetaObject(void)
{
    FUN_003b8ba0();
}

void beNDMWShopCtrl10_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beNDMWShopCtrl10_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_beNDMWShopCtrl10_ctorTable[0], 2);
    igMetaObject_NameFields(temp_s0, &g_beNDMWShopCtrl10_fieldTable[0], &DAT_004c9c60[0], &DAT_004c9c68[0], temp_s1);
}

