void FUN_003b6bc0(int arg0) {
    FUN_003b6cf0();
    igMetaObject_CreateInstance(*(int *)0x58ACC8, arg0);
}

void *FUN_003b6c00(void) {
    igMetaObject *g = g_beNDMWShopCtrlSales_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003b6cf0();
    }
    return g_beNDMWShopCtrlSales_metaObject[0];
}

int beNDMWShopCtrlSales_GetVTable(void) {
    struct Obj_3b6c50 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w13 = 0;
    obj.w14 = 0;
    obj.w15 = 0;
    obj.w16 = 0;
    obj.w17 = 0;
    obj.w18 = 0;
    obj.w19 = 0;
    obj.vt = &DAT_0053f8e0[0];
    obj.w24 = 0;
    obj.w25 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_0053f8e0[0];
    FUN_00226990(&obj.w25, -1);
    FUN_003b6090((void **)&obj.w24, (long long)(-1));
    FUN_003b6770((int **)&obj, (long long)0);
    return t;
}

void FUN_003b6cf0(void)
{
    igMetaObject_RunStaticInit(beNDMWShopCtrlSales_Register);
}

void *beNDMWShopCtrlSales_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWShopCtrlSales_metaObject,
        beNDMWListCtrl_Register,
        beNDMWListCtrl_GetPublishedMetaObject,
        beNDMWShopCtrlSales_GetMetaObject,
        beNDMWShopCtrlSales_className,
        0x68, /* instance size */
        beNDMWShopCtrlSales_GetVTable,
        beNDMWShopCtrlSales_InitFields,
        0, /* extra callback item */
        g_beNDMWShopCtrlSales_callbackList /* callback list */
    );
}

void beNDMWShopCtrlSales_GetMetaObject(void)
{
    FUN_003b6c00();
}

void beNDMWShopCtrlSales_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beNDMWShopCtrlSales_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c9998[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_003c9130();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_002cb110();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004c99a0[0], &DAT_004c99a8[0], &DAT_004c99b0[0], temp_s2);
}

