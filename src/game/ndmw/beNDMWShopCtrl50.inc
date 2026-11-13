void beNDMWShopCtrl50_Create(int arg0) {
    FUN_003b82e0();
    igMetaObject_CreateInstance(*(int *)0x58ADB8, arg0);
}

void *FUN_003b8210(void) {
    igMetaObject *g = g_beNDMWShopCtrl50_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003b82e0();
    }
    return g_beNDMWShopCtrl50_metaObject[0];
}

int beNDMWShopCtrl50_GetVTable(void) {
    struct W_3b8260 o;
    int r;

    igObject_InitHeader(&o);
    o.f[12] = 0;
    o.f[13] = 0;
    o.f[14] = 0;
    o.f[15] = 0;
    o.f[16] = 0;
    o.f[17] = 0;
    o.f[18] = 0;
    o.vt = DAT_0053fd30;
    r = *(int *)((char *)&o + *(int *)(((char * *)g_objectSystem)[0] + 916));
    o.vt = DAT_0053fd30;
    beNDMWWindowCtrl_Destroy((beNDMWWindowCtrl *)&o, (long long)0);
    return r;
}

void FUN_003b82e0(void)
{
    igMetaObject_RunStaticInit(beNDMWShopCtrl50_Register);
}

void *beNDMWShopCtrl50_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWShopCtrl50_metaObject,
        beNDMWWindowCtrl_Register,
        beNDMWWindowCtrl_GetPublishedMetaObject,
        beNDMWShopCtrl50_GetMetaObject,
        beNDMWShopCtrl50_className,
        0x68, /* instance size */
        beNDMWShopCtrl50_GetVTable,
        beNDMWShopCtrl50_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWShopCtrl50_GetMetaObject(void)
{
    FUN_003b8210();
}

void beNDMWShopCtrl50_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beNDMWShopCtrl50_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_beNDMWShopCtrl50_ctorTable[0], 5);
    igMetaObject_NameFields(temp_s0, &g_beNDMWShopCtrl50_fieldTable[0], &DAT_004c9bb0[0], &DAT_004c9bd0[0], temp_s1);
}

