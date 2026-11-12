void FUN_003b70e0(int arg0) {
    FUN_003b7200();
    igMetaObject_CreateInstance(*(int *)0x58AD10, arg0);
}

void *FUN_003b7120(void) {
    igMetaObject *g = g_beNDMWShopCtrlDeviceSell_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003b7200();
    }
    return g_beNDMWShopCtrlDeviceSell_metaObject[0];
}

int beNDMWShopCtrlDeviceSell_GetVTable(void) {
    Obj_3b7170 o;
    int r;

    igObject_InitHeader(&o);
    o.w[12] = 0;
    o.w[13] = 0;
    o.w[14] = 0;
    o.w[15] = 0;
    o.w[16] = 0;
    o.w[17] = 0;
    o.w[18] = 0;
    o.vt = &DAT_0053f9b0[0];
    o.s = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
    o.vt = &DAT_0053f9b0[0];
    FUN_00226990(&o.s, -1);
    FUN_003b6770((int **)&o, (long long)0);
    return r;
}

void FUN_003b7200(void)
{
    igMetaObject_RunStaticInit(beNDMWShopCtrlDeviceSell_Register);
}

void *beNDMWShopCtrlDeviceSell_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWShopCtrlDeviceSell_metaObject,
        beNDMWListCtrl_Register,
        beNDMWListCtrl_GetPublishedMetaObject,
        beNDMWShopCtrlDeviceSell_GetMetaObject,
        beNDMWShopCtrlDeviceSell_className,
        0x64, /* instance size */
        beNDMWShopCtrlDeviceSell_GetVTable,
        beNDMWShopCtrlDeviceSell_InitFields,
        0, /* extra callback item */
        g_beNDMWShopCtrlDeviceSell_callbackList /* callback list */
    );
}

void beNDMWShopCtrlDeviceSell_GetMetaObject(void)
{
    FUN_003b7120();
}

void beNDMWShopCtrlDeviceSell_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beNDMWShopCtrlDeviceSell_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c9a40[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_002cb110();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004c9a48[0], &DAT_004c9a50[0], &DAT_004c9a58[0], temp_s2);
}

